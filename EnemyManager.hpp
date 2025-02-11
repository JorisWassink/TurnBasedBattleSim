#pragma once
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include "gameObject.hpp"
#include "Button.hpp"
#include "player.hpp"
#include "Enemy.hpp"
#include "GenericLabel.hpp"


class EnemyManager : public GameObject {
private:
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
    void EnemyTurn(Player* target);
    Enemy* GetEnemy();
    void PlayerActionResponse(std::string action, int amount = 0, int secondAmount = 0);
    std::string getIdentifier() const;
};

