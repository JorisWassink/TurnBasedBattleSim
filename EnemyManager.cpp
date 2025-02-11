#pragma once
#include "EnemyManager.hpp"
#include "Button.hpp"
#include "Player.hpp"
#include "Enemy.hpp"


const float EnemyManager::TREMBLE_CHANCE = 10.0f;

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


void EnemyManager::EnemyTurn(Player* target) {
    label.textStr += "\rEnemy Turn!\n";

    int actionEnemyChance = random(1, 100);
    if (actionEnemyChance < EnemyManager::TREMBLE_CHANCE) {
        currentEnemy->Tremble(label);
    }
    else if (actionEnemyChance < 20) {
        currentEnemy->Recover(label);
    }
    else if (actionEnemyChance < 40) {
        currentEnemy->CastMagic(label, target);
    }
    else if (actionEnemyChance < 65) {
        currentEnemy->Prepare(label);
    }
    else if (actionEnemyChance > 65){
        currentEnemy->Attack(label, target);
    }
    target->playerTurn = true;
    label.textStr += "\rYour Turn!\n";

}


void EnemyManager::PlayerActionResponse(std::string action, int amount, int secondAmount) {
    if (action == "attack") {
        label.textStr += "\rPlayer Attacks and does " + std::to_string(amount) + " damage!\n";
    }
    if (action == "recover") {
        if (amount == 0) {
            label.textStr += "Player tries to heal but fails... \n";
        }
        else {
            label.textStr += "\rPlayer recovers " + std::to_string(amount) + " HP and " + std::to_string(secondAmount) + " SP!\n";
        }
    }
    if (action == "prepare") {
        label.textStr += "\rPlayer prepares...\n";
    }
    if (action == "magic") {
        label.textStr += "\rPlayer casts magic and does " + std::to_string(amount) + " damage!\n";
    }
    if (action == "dodge") {
        if (amount == 1) {
            label.textStr += "\rPlayer does awesome backflip and evades the attack!\n";
        }
        else {
            label.textStr += "\rPlayer tries to do a backflip but fails!\n";

        }
    }
}


void EnemyManager::Death() {
    if (currentEnemy != nullptr)
    {
        currentEnemy->Initialize(*this, currentEnemy->body.getScale(), currentEnemy->body.getPosition(), currentEnemy->body.getColor());
        label.textStr += "\rEnemy killed!\n";
    }   
}