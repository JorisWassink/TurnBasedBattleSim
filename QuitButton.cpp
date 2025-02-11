#include "QuitButton.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <string>

// Constructor 
QuitButton::QuitButton(std::string identifier, sf::Font& font, std::string buttonText,
    sf::Vector2f size, sf::Color color, sf::RenderWindow& window, sf::Vector2f place) : Button(identifier, font, buttonText, size, color, place)
    , font(font), buttonText(buttonText) {
    text.setFont(font);
    text.setString(buttonText);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(place);
    shape.setPosition(place);
    shape.setSize(size);
    shape.setFillColor(color);
    action = [&window]() {window.close();};
}

// Destructor 
QuitButton::~QuitButton() { }

// Update method (if necessary, can be left empty)
void QuitButton::update() { }

// Render the button and its text
void QuitButton::render(sf::RenderWindow& window) {
    window.draw(shape);  // Draw the button shape
    window.draw(text);   // Draw the button text
}

// Set the action for the button
void QuitButton::setButtonAction(std::function<void()> action) {
    this->action = action;
}

void QuitButton::onClick() {
    if (action) {
        action();  // Execute the assigned action if available
    }
}


