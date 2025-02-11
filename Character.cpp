#pragma once
#include "Character.hpp"

Character::Character(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Texture& texture)
{
	body.setTexture(texture);
	body.setPosition(position);
	body.setScale(size);
	body.setColor(color);

	healthBar.lPosition = position + sf::Vector2f(0, body.getTexture()->getSize().y / 2);
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


