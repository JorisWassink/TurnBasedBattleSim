#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "Button.hpp"
#include "Utils.hpp"

class PlayerStats : public GameObject {
private:
	int st = 1;
	int ag = 1;
	int ws = 1;

	sf::Font font;
	sf::Vector2f lPosition;

	sf::RectangleShape stShape;
	sf::RectangleShape agShape;
	sf::RectangleShape wsShape;

	sf::Text stText;
	sf::Text agText;
	sf::Text wsText;

	sf::Text stData;
	sf::Text agData;
	sf::Text wsData;

	sf::Vector2f buttonSize;

	Button randomizeButton;
public:
	PlayerStats(std::string id, sf::Vector2f position, sf::Vector2f buttonOffset);
	~PlayerStats();
public:
	void render(sf::RenderWindow& Window) override;
	void update() override;
	void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
	void randomizeStats();
	ThreeIntegers getStats();
};