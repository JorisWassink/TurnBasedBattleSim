#include "PlayButton.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <string>
#include <fstream>

// Constructor 
PlayButton::PlayButton(std::string identifier, sf::Font& font, std::string buttonText,
    sf::Vector2f size, sf::Color color, sf::RenderWindow& window, sf::Vector2f place, Scene* currentScene, Scene* nextScene) : Button(identifier, font, buttonText, size, color, place)
    , font(font), buttonText(buttonText) {


    text.setFont(font);
    text.setString(buttonText);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(place);

    shape.setPosition(place);
    shape.setSize(size);
    shape.setFillColor(color);
}

// Destructor 
PlayButton::~PlayButton() { }

// Update
void PlayButton::update() { }

// Render the button and its text
void PlayButton::render(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

void PlayButton::setButtonAction(std::function<void()> action) {
    this->action = action;
}

void PlayButton::onClick() {
    if (action) {
        action();
    }
}