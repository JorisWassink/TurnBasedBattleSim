#include "Button.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <string>

// Constructor 
Button::Button(std::string identifier, sf::Font& font, std::string buttonText,
    sf::Vector2f size, sf::Color color, sf::Vector2f place)
    : font(font), buttonText(buttonText) {
    text.setFont(font);
    text.setString(buttonText);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setOrigin(-place);

    shape.setOrigin(-place);
    shape.setSize(size);
    shape.setFillColor(color);
}

// Destructor 
Button::~Button() { }

// Handle events (like clicks)
void Button::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            // Check if the mouse is within the button's bounds
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                onClick();  // Call onClick if the button is clicked
            }
        }
    }
}

// Virtual function that can be overridden for specific button behavior
void Button::onClick() {
    if (action) {
        action();  // Execute the assigned action if available
    }
}

// Update method (if necessary, can be left empty)
void Button::update() { }

// Render the button and its text
void Button::render(sf::RenderWindow& window) {
    window.draw(shape);  // Draw the button shape
    window.draw(text);   // Draw the button text
}

// Set the action for the button
void Button::setButtonAction(std::function<void()> action) {
    this->action = action;
}

