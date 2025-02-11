#pragma once
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include "gameObject.hpp"
#include "Button.hpp"
#include "player.hpp"

class UI : public GameObject {
private:
    const std::string identifier;
    std::vector<GameObject*> listOfGameObjects;
    Button* attackButton;
    Button* recoverButton;
    Button* prepareButton;
    Button* magicButton;

    sf::Font font;

public:
    UI(std::string identifier, Player* player, Enemy* currentEnemy);
    ~UI();

public:
    void addGameObject(GameObject& object);
    void addGameObject(GameObject* object);
    void update();
    void render(sf::RenderWindow& window);
    void HandleObjectEvents(const sf::Event& event, sf::RenderWindow& window);
    std::string getIdentifier() const;
};

