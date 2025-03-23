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
};

class EnemyManager : public GameObject {
private:
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

public:
    void update();
    void render(sf::RenderWindow& window);
    void Death();

    void SortColumns(std::string fileName);

    void Breed();

    void EnemyTurn(Character* target);
    void CalculateUtilities(Character* target);
    Enemy* GetEnemy();
    void PlayerActionResponse(Action action, int amount = 0, int secondAmount = 0);
    std::string getIdentifier() const;
};

