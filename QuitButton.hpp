#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include "Button.hpp"



// typedef std::function<void()> buttonAction;
class QuitButton : public Button {

private:
    sf::Text text;
    sf::Font& font;
    sf::RectangleShape shape;
    sf::RenderWindow window;
    std::string buttonText;

    // QuitButtonAction action;
    std::function<void()> action;

public:
    QuitButton(std::string identifier, sf::Font& font, std::string QuitButtonText,
        sf::Vector2f size, sf::Color color, sf::RenderWindow& window, sf::Vector2f place);
    ~QuitButton();

    void update() override;
    void render(sf::RenderWindow& window) override;

    // void setQuitButtonAction(QuitButtonAction action);
    void setButtonAction(std::function<void()> action);
public:
    void onClick() override;
};
