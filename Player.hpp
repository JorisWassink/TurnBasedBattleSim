#pragma once
#include <SFML/Graphics.hpp>
#include "Character.hpp"
#include "Enemy.hpp"
#include "Utils.hpp"

class Player : public Character {
private:
	sf::Texture texture;
	sf::Sprite body;
	int pScore = 0;

public:
	Player(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Texture& texture);
	~Player();
public:
	bool charged;
	void Initialize(sf::Vector2f position, sf::Vector2f size, sf::Color color);
	void update() override;
	void Turn(Character& target) override;
	void Attack(Enemy* target);
	void Recover(Enemy* target);
	void Prepare(Enemy* target);
	void Magic(Enemy* target);
	void Dodge(Enemy* target);
	bool CheckDeath() override;
	void SetStats(ThreeIntegers stats);
};


