#pragma once
#include <SFML/Graphics.hpp>
#include "Character.hpp"
#include "GenericLabel.hpp"


class EnemyManager;

class Enemy : public Character {
private:


public:
	EnemyManager& manager;
	sf::Sprite body;
	bool charged{};
	float agressiveness = 1;

	float attackChance;
	float prepareChance;
	float recoverChance;
	float lowMagicChance;
	float highMagicChance;

	float fitness;


	Enemy(sf::Vector2f position, sf::Vector2f size, sf::Color color, EnemyManager& manage, sf::Texture& texture);

	~Enemy();
public:
	//void render(sf::RenderWindow& Window) override;

	void update() override;
	void SetStats();
	bool CheckDeath() override;

	void WriteValues(bool won);

	void Turn(Character& target) override;

	void Initialize(EnemyManager& manage, sf::Vector2f size, sf::Vector2f position, sf::Color color);
	void Initialize(Enemy& enemy);

	//I put these in enemy instead of in Character to prevent circular dependancy
	void Prepare(GenericLabel& label);
	void Recover(GenericLabel& label);
	void CastMagic(GenericLabel& label, Character* target);
	void Tremble(GenericLabel& label);
	void Attack(GenericLabel& label, Character* target);
};


