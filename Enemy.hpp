#pragma once
#include <SFML/Graphics.hpp>
#include "Character.hpp"
#include "GenericLabel.hpp"


class EnemyManager;

class Player;

class Enemy : public Character {
private:
	
	

public:
	EnemyManager& manager;
	sf::Sprite body;
	bool charged;
	Enemy(sf::Vector2f position, sf::Vector2f size, sf::Color color, EnemyManager& manage, sf::Texture& texture);

	~Enemy();
public:
	//void render(sf::RenderWindow& Window) override;
	void update() override;
	void SetStats();
	bool CheckDeath();
	void Initialize(EnemyManager& manage, sf::Vector2f size, sf::Vector2f position, sf::Color color);
	void Initialize(Enemy& enemy);

	//I put these in enemy instead of in Character to prevent circular dependancy
	void Prepare(GenericLabel& label);
	void Recover(GenericLabel& label);
	void CastMagic(GenericLabel& label, Player* target);
	void Tremble(GenericLabel& label);
	void Attack(GenericLabel& label, Player* target);
};


