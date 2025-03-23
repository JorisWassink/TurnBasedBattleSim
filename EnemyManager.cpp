#pragma once
#include "EnemyManager.hpp"

#include <fstream>
#include <thread>
#include <iostream>
#include <chrono>
#include <future>
#include <numeric>
#include <sstream>

#include "Button.hpp"
#include "Player.hpp"
#include "Enemy.hpp"



std::map<Action, float> utilities = {
    { ATTACK, 0 },
    { PREPARE, 0 },
    { MAGIC, 0 },
    { RECOVER, 0 },
};

EnemyManager::EnemyManager(std::string identifier, sf::Vector2f location, GenericLabel& textLabel) : identifier(identifier), location(location), label(textLabel)
{
    texture.loadFromFile("textures/Evil.png");
    currentEnemy = new Enemy(sf::Vector2f(location.x + texture.getSize().x, location.y),
        sf::Vector2f(.5f, .5f),
        sf::Color::White, *this, texture);
}

EnemyManager::~EnemyManager() {
    delete currentEnemy;
}

void EnemyManager::render(sf::RenderWindow& window) {
    currentEnemy->render(window);
}

void EnemyManager::update() {
    if (currentEnemy != nullptr) {
        currentEnemy->update();
    }
}

Enemy* EnemyManager::GetEnemy() 
{
    return currentEnemy;
}

std::string EnemyManager::getIdentifier() const {
    return this->identifier;
}

Action getHighestAction(const std::map<Action, float>& actionMap) {
    float totalValue = 0.0f;

    for (const auto& entry : actionMap) {
        totalValue += entry.second;
    }

    float randomValue = randomf(0, totalValue);

    float buffer = 0;
    for (const auto& entry : actionMap) {
        if ((entry.second + buffer) > randomValue) {

            std::ofstream file("results.csv", std::ios::app); // Append mode
            if (file.is_open()) {
                file << entry.first << "\n"; // Write action name & result
            } else {
                std::cerr << "Failed to open results.csv\n";
            }
            return entry.first;
        }
        buffer += entry.second;
    }
}

void EnemyManager::CalculateUtilities(Character* target) {
    float healthPercentage = (currentEnemy->health / currentEnemy->maxHealth);
    float targetHealthPercentage = target->health / target->maxHealth;

    float recoverChance = (1 - healthPercentage) / ((currentEnemy->recoverChance * healthPercentage) + 1);

    float attackChance = (1 - targetHealthPercentage) / ((2 * targetHealthPercentage) + 1) * currentEnemy->attackChance;

    float prepareChance = currentEnemy->charged ? 0 : currentEnemy->prepareChance;

    float magicChance = currentEnemy->charged ? currentEnemy->highMagicChance : currentEnemy->lowMagicChance;

    utilities[RECOVER] = recoverChance;
    utilities[ATTACK] = attackChance;
    utilities[PREPARE] = prepareChance;
    utilities[MAGIC] = magicChance;
}

void EnemyManager::EnemyTurn(Character* target) {
    label.SetString("\rEnemy Turn!\n");
    currentEnemy->fitness += 2;
    CalculateUtilities(target);

    Awaitable awaitable;
    awaitable([this, target] {
        switch (getHighestAction(utilities)) {
            case ATTACK:
                currentEnemy->Attack(label, target);
            break;
            case PREPARE:
                currentEnemy->Prepare(label);
            break;
            case MAGIC:
                currentEnemy->CastMagic(label, target);
            break;
            case RECOVER:
                currentEnemy->Recover(label);
            break;
            default:
                throw new std::exception;
        }


        Awaitable awaitable2;
        awaitable2([this, target] {
            target->Turn(*currentEnemy);
            label.textStr += "\rYour Turn!\n";
        });

    });

}

void EnemyManager::PlayerActionResponse(enum Action action , int amount, int secondAmount) {
    switch (action) {
        case ATTACK:
            label.textStr += "\rPlayer Attacks and does " + std::to_string(amount) + " damage!\n";
            break;
        case RECOVER:
            if (amount == 0)
                label.textStr += "Player tries to heal but fails... \n";
            else
                label.textStr += "\rPlayer recovers " + std::to_string(amount) + " HP and " + std::to_string(secondAmount) + " SP!\n";
            break;
        case PREPARE:
            label.textStr += "\rPlayer prepares...\n";
            break;
        case MAGIC:
            label.textStr += "\rPlayer casts magic and does " + std::to_string(amount) + " damage!\n";
            break;
        case DODGE:
            if (amount == 1)
                label.textStr += "\rPlayer does awesome backflip and evades the attack!\n";
            else
                label.textStr += "\rPlayer tries to do a backflip but fails!\n";
            break;
        default:
            throw std::invalid_argument("Invalid action!");
    }
}

void EnemyManager::Death() {
    if (currentEnemy != nullptr)
    {
        printf("amount of enemies left: %f \n", enemyList.size());
        if(enemyList.size() <= 0) {
            printf("making new enemies... \n");
            SortColumns("bestEnemy.csv");
            Breed();
        }
        currentEnemy->Initialize(*enemyList.begin());
        enemyList.erase(enemyList.begin());
        label.textStr += "\rEnemy killed!\n";
    }   
}

void EnemyManager::SortColumns(std::string fileName) {
    std::ifstream inputFile(fileName);
    std::vector<std::vector<double>> data;

    if (!inputFile) {
        std::cerr << "Error: Could not open file for reading." << std::endl;
        return;
    }


    std::string line;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::vector<double> row;
        double value;
        while (ss >> value) {
            row.push_back(value);
        }
        data.push_back(row);
    }
    inputFile.close();

    if (data.empty()) {
        std::cerr << "Error: No data to sort." << std::endl;
        return;
    }

    size_t numCols = data[0].size();
    std::vector<std::vector<double>> columns(numCols);

    for (size_t i = 0; i < numCols; ++i) {
        for (size_t j = 0; j < data.size(); ++j) {
            columns[i].push_back(data[j][i]);
        }
    }

    for (auto& col : columns) {
        std::sort(col.begin(), col.end());
    }

    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < numCols; ++j) {
            data[i][j] = columns[j][i];
        }
    }

    std::sort(data.begin(), data.end(), [](const std::vector<double>& a, const std::vector<double>& b) {
        return a.size() > 5 && b.size() > 5 && a[5] > b[5];
    });

    if (data.size() > 10) {
        data.resize(10);
    }

    std::ofstream outputFile(fileName);
    if (!outputFile) {
        std::cerr << "Error: Could not open file for writing." << std::endl;
        return;
    }



    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            outputFile << row[i];
            if (i < row.size() - 1) {
                outputFile << " ";
            }
        }
        outputFile << "\n";
    }

    enemyList.clear();

    for (size_t i = 0; i < data.size(); ++i) {
        EnemyStats enemy = {
            static_cast<float>(data[i][0]),
            static_cast<float>(data[i][1]),
            static_cast<float>(data[i][2]),
            static_cast<float>(data[i][3]),
            static_cast<float>(data[i][4]),
        };
        enemyList.push_back(enemy);
        printf("enemy pushed \n");
    }
    

    outputFile.close();
}

void EnemyManager::Breed() {
    std::list<EnemyStats> offspringEnemies;
    std::list<EnemyStats> startEnemies(enemyList.begin(), enemyList.end());

    while (startEnemies.size() > 0) {
        EnemyStats parentOne = startEnemies.front();
        EnemyStats parentTwo = startEnemies.back();
        EnemyStats offspring;
        offspring.attackChance = random(0,1) ? parentOne.attackChance : parentTwo.attackChance;
        offspring.prepareChance = random(0,1) ? parentOne.prepareChance : parentTwo.prepareChance;
        offspring.recoverChance = random(0,1) ? parentOne.recoverChance : parentTwo.recoverChance;
        offspring.lowMagicChance = random(0, 1) ? parentOne.lowMagicChance : parentTwo.lowMagicChance;
        offspring.highMagicChance = random(0, 1) ? parentOne.highMagicChance : parentTwo.highMagicChance;
        startEnemies.erase(std::find(startEnemies.begin(), startEnemies.end(), parentOne));
        startEnemies.erase(std::find(startEnemies.begin(), startEnemies.end(), parentTwo));
        offspringEnemies.push_back(offspring);
        printf("made offspring \n");
    }

    //mutation
    for (auto& offspring: offspringEnemies) {
        float mutationAmount = randomf(0.8, 1.2);
        switch(random(0,4)) {
            case 0:
                offspring.attackChance *= mutationAmount;
            break;
            case 1:
                offspring.prepareChance *= mutationAmount;
            break;
            case 2:
                offspring.recoverChance *= mutationAmount;
            break;
            case 3:
                offspring.lowMagicChance *= mutationAmount;
            break;
            case 4:
                offspring.highMagicChance *= mutationAmount;
            break;
            default:
                throw std::invalid_argument("Invalid offspring chance!");
        }
        printf("mutated with a value of %f \n", mutationAmount);
    }

    for (auto offspring: offspringEnemies) {
        printf("offspring has an attack of %f \n", offspring.recoverChance);
    }

    enemyList.clear();
    enemyList = offspringEnemies;
}