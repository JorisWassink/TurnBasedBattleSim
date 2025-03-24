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
	const size_t pos = text.find('\n');
	if (pos != std::string::npos) {
		text.erase(0, pos + 1);
	}
}

void GenericLabel::SetString(const std::string &textS) {
	textStr += textS;
}


void GenericLabel::render(sf::RenderWindow& window) {
	std::lock_guard<std::mutex> lock(textMutex);  // Ensure safe access to `textStr`
	text.setString(textStr);
	text.setPosition(lPosition.x - (text.getLocalBounds().width/2.0f), lPosition.y);
	window.draw(text);
}

void GenericLabel::update() {
	if (textStr.length() > 150) {
		RemoveFirstLine(textStr);
	}
}