#pragma once
#include "Character.hpp"

Character::Character(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Texture& texture)
{
	healthBar.lPosition = position + sf::Vector2f(0, size.y * 1.2f);


	body.setTexture(texture);
	body.setPosition(position);
	body.setScale(size);
	body.setColor(color);
	AddChild(healthBar);
}

Character::~Character() {}

void Character::render(sf::RenderWindow& window) 
{

	healthBar.textStr = "Health: " + std::to_string(health);
	healthBar.render(window);
	window.draw(body);
}

void Character::update(){}


