#pragma once
#include "Character.hpp"

#include "Utils.hpp"

Character::Character(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Texture& texture): animator(Animator()) {

	body.setTexture(texture);
	body.setScale(size);
	body.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	body.setPosition(position);
	body.setColor(color);

	animator.setBody(body);

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


