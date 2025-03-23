#pragma once
#include <SFML/Graphics.hpp>

#include "Animator.hpp"
#include "GameObject.hpp"
#include "GenericLabel.hpp"


enum Action {
	ATTACK,
	PREPARE,
	RECOVER,
	MAGIC,
	TREMBLE,
	DODGE
  };

class Character : public GameObject {
private:
	sf::Texture texture;
	sf::Vector2f cPosition;

public:
	bool turn;
	Animator animator;
	sf::Sprite body;
	int maxHealth;
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
	virtual bool CheckDeath();
	virtual void Turn(Character& target);

};


