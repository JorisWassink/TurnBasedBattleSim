#pragma once
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include "gameObject.hpp"
#include "Button.hpp"
#include "player.hpp"
#include "Enemy.hpp"
#include "GenericLabel.hpp"


struct EnemyStats {
    float attackChance;
    float prepareChance;
    float recoverChance;
    float lowMagicChance;
    float highMagicChance;

    bool operator==(const EnemyStats& other) const {
        return attackChance == other.attackChance &&
               prepareChance == other.prepareChance &&
               recoverChance == other.recoverChance &&
               lowMagicChance == other.lowMagicChance &&
               highMagicChance == other.highMagicChance;
    }
};

class Enemy;

class EnemyManager : public GameObject {
private:
    int enemyAmount = 0;
    std::list<EnemyStats> enemyList;
    const std::string identifier;
    Enemy* currentEnemy;
    sf::Vector2f location;
    GenericLabel& label;
    sf::Texture texture;
    const static float TREMBLE_CHANCE;


public:
    EnemyManager(std::string identifier, sf::Vector2f location, GenericLabel& textLabel);
    ~EnemyManager();
    Enemy* GetEnemy();

public:
    void update();
    void render(sf::RenderWindow& window);
    void Death();

    void SortColumns(std::string fileName);

    void Breed();

    void EnemyTurn(Character* target);
    void CalculateUtilities(Character* target);

    void PlayerActionResponse(Action action, int amount = 0, int secondAmount = 0);
    std::string getIdentifier() const;
};

