#pragma once
#include "UI.hpp"
#include "Button.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

UI::UI(std::string identifier, Player* player, Enemy* curentEnemy) : GameObject(identifier)
{
    font.loadFromFile("arial.ttf");

    attackButton = new Button("attackbutton001", font, "attack", sf::Vector2f(100, 50), sf::Color::Cyan, sf::Vector2f(20, 20));
    recoverButton = new Button("recoverbutton001", font, "recover", sf::Vector2f(100, 50), sf::Color::Cyan, sf::Vector2f(140, 20));
    prepareButton = new Button("preparebutton001", font, "prepare", sf::Vector2f(100, 50), sf::Color::Cyan, sf::Vector2f(260, 20));
    magicButton = new Button("magicbutton001", font, "magic", sf::Vector2f(100, 50), sf::Color::Cyan, sf::Vector2f(380, 20));

    attackButton->setButtonAction([player, curentEnemy]() {
        if (player->turn) {
            player->Attack(curentEnemy);
        }
    });

    recoverButton->setButtonAction([player, curentEnemy]() {
        if (player->turn) {
            player->Recover(curentEnemy);
        }
    });

    prepareButton->setButtonAction([player, curentEnemy]() {
        if (player->turn) {
            player->Prepare(curentEnemy);
        }
    });

    magicButton->setButtonAction([player, curentEnemy]() {
        if (player->turn) {
            player->Magic(curentEnemy);
        }
    });

    
    this->addGameObject(attackButton);
    this->addGameObject(recoverButton);
    this->addGameObject(prepareButton);
    this->addGameObject(magicButton);

}

UI::~UI() {
    delete attackButton;
}

void UI::addGameObject(GameObject& object) {
    this->listOfGameObjects.push_back(&object);
}


void UI::addGameObject(GameObject* object) {
    if (object == nullptr) return;
    this->listOfGameObjects.push_back(object);
}

void UI::update() {
    for (unsigned int i = 0; i < this->listOfGameObjects.size(); i++) {
        this->listOfGameObjects[i]->update();
    }
}

void UI::render(sf::RenderWindow& window) {
    for (unsigned int i = 0; i < this->listOfGameObjects.size(); i++) {
        this->listOfGameObjects[i]->render(window);
    }
}

void UI::HandleObjectEvents(const sf::Event& event, sf::RenderWindow& window) {
    for (unsigned int i = 0; i < this->listOfGameObjects.size(); i++) {
        this->listOfGameObjects[i]->handleEvent(event, window);
    }
}

std::string UI::getIdentifier() const {
    return this->identifier;
}
