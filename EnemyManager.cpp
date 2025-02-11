#pragma once
#include "EnemyManager.hpp"
#include "Button.hpp"
#include "Player.hpp"
#include "Enemy.hpp"


const float EnemyManager::TREMBLE_CHANCE = 10.0f;

std::map<Action, float> utilities = {
    { ATTACK, 0 },
    { PREPARE, 0 },
    { MAGIC, 0 },
    { RECOVER, 0 },
};

EnemyManager::EnemyManager(std::string identifier, sf::Vector2f location, GenericLabel& textLabel) : identifier(identifier), location(location), label(textLabel)
{

    texture.loadFromFile("textures/player1.png");
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
    Action highestAction = actionMap.begin()->first;  // Begin met de eerste actie
    int highestValue = actionMap.begin()->second;  // Begin met de waarde van de eerste actie

    // Door de map heen lopen om de actie met de hoogste waarde te vinden
    for (const auto& entry : actionMap) {
        if (entry.second > highestValue) {
            highestAction = entry.first;  // Bijwerken van de actie met de hoogste waarde
            highestValue = entry.second;  // Bijwerken van de hoogste waarde
        }
    }

    return highestAction;
}

void EnemyManager::CalculateUtilities() {
    utilities[RECOVER] = .9f;
    utilities[PREPARE] = 1.5f;
}


void EnemyManager::EnemyTurn(Player* target) {
    label.textStr += "\rEnemy Turn!\n";

    CalculateUtilities();

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
    }
    target->playerTurn = true;
    label.textStr += "\rYour Turn!\n";


    // int actionEnemyChance = random(1, 100);
    // if (actionEnemyChance < EnemyManager::TREMBLE_CHANCE) {
    //     currentEnemy->Tremble(label);
    // }
    // else if (actionEnemyChance < 20) {
    //     currentEnemy->Recover(label);
    // }
    // else if (actionEnemyChance < 40) {
    //     currentEnemy->CastMagic(label, target);
    // }
    // else if (actionEnemyChance < 65) {
    //     currentEnemy->Prepare(label);
    // }
    // else if (actionEnemyChance > 65){
    //     currentEnemy->Attack(label, target);
    // }
    // target->playerTurn = true;
    // label.textStr += "\rYour Turn!\n";

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
        currentEnemy->Initialize(*this, currentEnemy->body.getScale(), currentEnemy->body.getPosition(), currentEnemy->body.getColor());
        label.textStr += "\rEnemy killed!\n";
    }   
}