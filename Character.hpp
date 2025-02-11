#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "GenericLabel.hpp"


class Character : public GameObject {
private:
	sf::Texture texture;
	sf::Sprite body;
	sf::Vector2f cPosition;

public:
	int health;
	int strength;
	int agility;
	int wits;
	int sanity;
	GenericLabel healthBar;

	Character(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Texture& texture);
	~Character();
public:
	void render(sf::RenderWindow& Window) override;
	void update() override;
};


