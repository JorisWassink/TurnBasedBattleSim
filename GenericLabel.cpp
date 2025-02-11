#include "GenericLabel.hpp"

GenericLabel::GenericLabel(const std::string &textS, const sf::Vector2f position) : GameObject("id") {
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Green);
	text.setString(textS);
	lPosition = position;
	textStr = textS;
}

GenericLabel::~GenericLabel() = default;

void RemoveFirstLine(std::string& text) {
	const size_t pos = text.find('\n'); // Find the position of the first newline
	if (pos != std::string::npos) {
		text.erase(0, pos + 1); // Erase from the beginning up to the newline
	}
}

void GenericLabel::render(sf::RenderWindow& window) {
	text.setString(textStr);
	text.setPosition(lPosition);
	window.draw(text);
}

void GenericLabel::update() {
	if (textStr.length() > 150) {
		RemoveFirstLine(textStr);
	}
}