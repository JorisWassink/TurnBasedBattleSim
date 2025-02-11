#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

#include "GameObject.hpp"

// typedef std::function<void()> buttonAction;
class Button : public GameObject {

private:
    sf::Text text;
    sf::Font& font;
    sf::RectangleShape shape;
    std::string buttonText;

    std::function<void()> action;

public:
    Button(std::string identifier, sf::Font& font, std::string buttonText,
        sf::Vector2f size, sf::Color color, sf::Vector2f place);
    ~Button();

    void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;

    virtual void update() override;
    virtual void render(sf::RenderWindow& window) override;

    virtual void setButtonAction(std::function<void()> action);

public:
    virtual void onClick();
};
