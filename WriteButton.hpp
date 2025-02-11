#pragma once
#include <functional>

#include "Button.hpp"

// typedef std::function<void()> buttonAction;
class WriteButton : public Button {

private:
    sf::Text text;
    sf::Font& font;
    sf::RectangleShape shape;
    sf::RenderWindow window;
    std::string buttonText;

    std::function<void()> action;

public:
    WriteButton(std::string identifier, sf::Font& font, std::string QuitButtonText,
        sf::Vector2f size, sf::Color color, sf::RenderWindow& window, std::string doc, sf::Vector2f place);
    ~WriteButton();

    void update() override;
    void render(sf::RenderWindow& window) override;

    // void setQuitButtonAction(QuitButtonAction action);
    void setButtonAction(std::function<void()> action);
public:
    void onClick() override;
};
