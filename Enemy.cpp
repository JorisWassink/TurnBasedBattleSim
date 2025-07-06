#pragma once
#include "Enemy.hpp"

#include <fstream>

#include "Utils.hpp"
#include "EnemyManager.hpp"
#include <math.h>


Enemy::Enemy(sf::Vector2f position, sf::Vector2f size, sf::Color color, EnemyManager& manage, sf::Texture& texture, std::string id) : Character(position, size, color, texture, id), manager(manage)
{
	Initialize();
}

Enemy::~Enemy() = default;

void Enemy::update() {}



void Enemy::Initialize(EnemyStats stats)
{
	SetStats(stats);
}

void Enemy::Initialize()
{
	EnemyStats stats {1,1,1,1, 1};
	SetStats(stats);
}

void Enemy::SetStats(EnemyStats stats) {
	fitness = 0;

	strength = 3;
	agility = 3;
	wits = 3;

	maxHealth = strength * 3;
	health = maxHealth;
	sanity = wits * 2;

	attackChance = stats.attackChance;
	prepareChance = stats.prepareChance;
	recoverChance = stats.recoverChance;
	lowMagicChance = stats.lowMagicChance;
	highMagicChance = stats.highMagicChance;
}

void Enemy::Attack(GenericLabel& label, Character* target)  {
	bool attackingDone = false;
	while(attackingDone == false) {
		attackingDone = animator.HeadButt(.1f);
	}

	int damage;


	damage = random(strength + 2, agility * 2) - ceilf(target->strength / 2);



	if (damage <= 0) damage = 1;

	target->health -= damage;

	fitness += damage;

	label.textStr += "\renemy attacks and does " + std::to_string(damage) + " damage\n";

	if(target->health <= 0) {
		Enemy* enemyTarget = dynamic_cast<Enemy*>(target);
		if (enemyTarget) {
			enemyTarget->WriteValues(false);
		}

		WriteValues(true);
	}
}

void Enemy::Prepare(GenericLabel& label) {
	bool spinningDone = false;
	while(spinningDone == false) {
		spinningDone = animator.Backflip(.1f);
	}
	charged = true;
	label.textStr += "\renemy prepares\n";
}

void Enemy::Recover(GenericLabel& label) {
	int sanit = 0;
	if (random(1, 100) > (ceilf(1.5 * wits) * 11)) {
		int healing = 0;
		healing += random(0, 3);
		sanit += random(1, 2);
		health += healing;
		sanity += sanit;
	}
	label.textStr += "\renemy recovers " + std::to_string(sanit) + " sanity and " + std::to_string(wits) + " HP!\n";
}

void Enemy::CastMagic(GenericLabel& label, Character* target) {
	int damage;

	if (charged)
		damage = wits * 2;
	else
		damage = wits;


	target->health -= damage;


	fitness += damage;

	label.textStr += "\renemy casts magic and does " + std::to_string(damage) + " damage\n";
	if(target->CheckDeath()) {
		Enemy* enemyTarget = dynamic_cast<Enemy*>(target);
		if (enemyTarget) {
			enemyTarget->WriteValues(false);
		}
	}
}

void Enemy::Tremble(GenericLabel& label) {
	label.textStr += "\renemy trembles in fear...\n";
}

void Enemy::Turn(Character *target) {
	manager.EnemyTurn(target);
}


bool Enemy::CheckDeath() {
	if (health <= 0) {
		WriteValues(false);
		return true;
	}
	else {
		return false;
	}
}

static int count = 0;

void Enemy::WriteValues(bool won) {
	if (won)
		fitness += health * 1.5f;

	std::ofstream myFileWrite("bestEnemy.csv", std::ios::app); // Append mode
	std::ofstream myFileWrite2("EnemyList.csv", std::ios::app); // Append mode


	if (myFileWrite) {
		// Array of values to be written
		std::vector<float> values = { attackChance, prepareChance, recoverChance, lowMagicChance, highMagicChance, fitness };

		// Write the values, ensuring no extra comma after the last value
		for (size_t i = 0; i < values.size(); ++i) {
			myFileWrite << values[i];
			if (i < values.size() - 1) {
				myFileWrite << " ";
			}
		}

		// End the line after the values are writtenA
		myFileWrite << "\n";
	} else {
		std::cerr << "Error: Could not open file for writing." << std::endl;
	}

	myFileWrite.close();

	if (myFileWrite2) {
		count++;
		if(won && count % 5 == 0) {
			// Array of values to be written
			std::vector<float> values = { attackChance, prepareChance, recoverChance, lowMagicChance, highMagicChance, fitness };

			// Write the values, ensuring no extra comma after the last value
			for (size_t i = 0; i < values.size(); ++i) {
				myFileWrite2 << values[i];
				if (i < values.size() - 1) {
					myFileWrite2 << ",";
				}
			}

			// End the line after the values are written
			myFileWrite2 << "\n";
		}
	} else {
		std::cerr << "Error: Could not open file for writing." << std::endl;
	}

	myFileWrite2.close();

	if (!won)
		manager.Death();

}
