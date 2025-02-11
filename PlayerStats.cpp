#pragma once
#include "PlayerStats.hpp"
#include <math.h>
#include <iostream>;

PlayerStats::PlayerStats(std::string id, sf::Vector2f position, sf::Vector2f buttonOffset) : GameObject(id), buttonSize(40,100), 
	randomizeButton("", font, "Randomize", sf::Vector2f(150,50), sf::Color::Magenta, sf::Vector2f(position.x - 75, position.y - 150)) 

{
	randomizeButton.setButtonAction([&]() {
		randomizeStats();
	});

	font.loadFromFile("arial.ttf");

	stText.setFont(font);
	agText.setFont(font);
	wsText.setFont(font);

	stData.setFont(font);
	agData.setFont(font);
	wsData.setFont(font);

	stText.setCharacterSize(24);
	agText.setCharacterSize(24);
	wsText.setCharacterSize(24);

	stData.setCharacterSize(24);
	agData.setCharacterSize(24);
	wsData.setCharacterSize(24);

	stText.setFillColor(sf::Color::White);
	agText.setFillColor(sf::Color::White);
	wsText.setFillColor(sf::Color::White);

	stData.setFillColor(sf::Color::Black);
	agData.setFillColor(sf::Color::Black);
	wsData.setFillColor(sf::Color::Black);

	stShape.setPosition(position - buttonSize * 0.5f - buttonOffset);
	stShape.setSize(buttonSize);
	stShape.setFillColor(sf::Color::Red);

	agShape.setPosition(position - buttonSize * 0.5f);
	agShape.setSize(buttonSize);
	agShape.setFillColor(sf::Color::Green);

	wsShape.setPosition(position - buttonSize * 0.5f + buttonOffset);
	wsShape.setSize(buttonSize);
	wsShape.setFillColor(sf::Color::Blue);

	stText.setPosition(sf::Vector2f(stShape.getPosition().x, stShape.getPosition().y + stShape.getSize().y));
	agText.setPosition(sf::Vector2f(agShape.getPosition().x, agShape.getPosition().y + agShape.getSize().y));
	wsText.setPosition(sf::Vector2f(wsShape.getPosition().x, wsShape.getPosition().y + wsShape.getSize().y));

	stData.setPosition(stShape.getPosition());
	agData.setPosition(agShape.getPosition());
	wsData.setPosition(wsShape.getPosition());

	stText.setString("Strength");
	agText.setString("Agility");
	wsText.setString("Wits");
}

PlayerStats::~PlayerStats() { }


void PlayerStats::render(sf::RenderWindow& window) {
	stData.setString(std::to_string(st));
	agData.setString(std::to_string(ag));
	wsData.setString(std::to_string(ws));

	window.draw(stShape);
	window.draw(agShape);
	window.draw(wsShape);

	window.draw(stText);
	window.draw(agText);
	window.draw(wsText);

	window.draw(stData);
	window.draw(agData);
	window.draw(wsData);

	randomizeButton.render(window);
}

void PlayerStats::update() {
}

void PlayerStats::handleEvent(const sf::Event& event, sf::RenderWindow& window) 
{
	randomizeButton.handleEvent(event, window);
}



ThreeIntegers PlayerStats::getStats() {
	return {st, ag, ws};
}

void PlayerStats::randomizeStats() {
	st = 1;
	ag = 0;
	ws = 1;

	for (int i = 0; i < 6; i++)
	{
		switch (random(1,3)) {
			case 1:
				st++;
				break;
			case 2:
				ag++;
				break;
			case 3:
				ws++;
				break;

			default:
				throw new _exception();
		}
	}
}
