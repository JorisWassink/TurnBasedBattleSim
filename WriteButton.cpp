#include "WriteButton.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <string>
#include <fstream>

// Constructor 
WriteButton::WriteButton(std::string identifier, sf::Font& font, std::string buttonText,
    sf::Vector2f size, sf::Color color, sf::RenderWindow& window, std::string doc, sf::Vector2f place) : Button(identifier, font, buttonText, size, color, place)
    , font(font), buttonText(buttonText) {


    text.setFont(font);
    text.setString(buttonText);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setOrigin(place);

    shape.setOrigin(place);
    shape.setSize(size);
    shape.setFillColor(color);

    action = [&window, doc]()
        {
            std::ofstream myFileRead(doc);

            for (unsigned int i = 1; i < 6; i++) {
                myFileRead << "0 ";
            }
            myFileRead.close();
        };
}

// Destructor 
WriteButton::~WriteButton() { }

// Update
void WriteButton::update() { }

// Render the button and its text
void WriteButton::render(sf::RenderWindow& window) {
    window.draw(shape);  
    window.draw(text);   
}

void WriteButton::setButtonAction(std::function<void()> action) {
    this->action = action;
}

void WriteButton::onClick() {
    if (action) {
        action();  
    }
}