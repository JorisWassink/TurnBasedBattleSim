#pragma once
#include <SFML/Graphics.hpp>
#include "Character.hpp"
#include "EnemyManager.hpp"
#include "GenericLabel.hpp"


class EnemyManager;
struct  EnemyStats;

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


	Enemy(sf::Vector2f position, sf::Vector2f size, sf::Color color, EnemyManager& manage, sf::Texture& texture, std::string id);

	~Enemy();
public:
	//void render(sf::RenderWindow& Window) override;

	void update() override;

	void Initialize(EnemyStats stats);

	void SetStats(EnemyStats stats);
	bool CheckDeath() override;

	void WriteValues(bool won);

	void Turn(Character* target) override;

	void Initialize();

	//I put these in enemy instead of in Character to prevent circular dependancy
	void Prepare(GenericLabel& label);
	void Recover(GenericLabel& label);
	void CastMagic(GenericLabel& label, Character* target);
	void Tremble(GenericLabel& label);
	void Attack(GenericLabel& label, Character* target);
};


