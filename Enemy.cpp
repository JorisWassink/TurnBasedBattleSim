#pragma once
#include "Enemy.hpp"

#include <fstream>

#include "Utils.hpp"
#include "EnemyManager.hpp"
#include <math.h>


Enemy::Enemy(sf::Vector2f position, sf::Vector2f size, sf::Color color, EnemyManager& manage, sf::Texture& texture) : Character(position, size, color, texture), manager(manage)
{
	Initialize(manage, position, size, color);
}

Enemy::~Enemy() = default;

void Enemy::update() {}

void Enemy::Initialize(EnemyManager& manage, sf::Vector2f size, sf::Vector2f position, sf::Color color)
{
	SetStats();
}

void Enemy::Initialize(Enemy& enemy)
{
	SetStats();
}

void Enemy::SetStats() {
	fitness = 0;

	strength = 3;
	agility = 3;
	wits = 3;

	maxHealth = strength * 3;
	health = maxHealth;
	sanity = wits * 2;


	std::ifstream myFileRead("bestEnemy.cmgt");

	if (myFileRead) {
		// Reset the cursor to the beginning of the file to read high scores
		myFileRead.clear(); // Clear EOF flag
		myFileRead.seekg(0); // Move cursor to the start of the file

		float chanceValue;

		int valuesRead = 0;
		while (myFileRead >> chanceValue && valuesRead < 5) {
			switch (valuesRead) {
				case 0: attackChance = chanceValue; break;
				case 1: prepareChance = chanceValue; break;
				case 2: recoverChance = chanceValue; break;
				case 3: lowMagicChance = chanceValue; break;
				case 4: highMagicChance = chanceValue; break;
			}
			valuesRead++;
		}

		if (valuesRead < 5) {
			printf("Warning: Less than 5 values read from the file, initializing to random values.\n");
			for (unsigned int i = 0; i < 5; i++) {
				attackChance = 0;
				prepareChance = 0;
				recoverChance = 0;
				lowMagicChance = 0;
				highMagicChance = 0;
			}
		}

		int randomValue = random(1, 5);

		switch (randomValue) {
			case 1:
				attackChance = randomf(0, 1);
				break;
			case 2:
				prepareChance = randomf(0, 1);
				break;
			case 3:
				recoverChance = randomf(0, 1);
				break;
			case 4:
				lowMagicChance = randomf(0, 1);
				break;
			case 5:
				highMagicChance = randomf(0, 1);
				break;
			default:
				printf("not working.\n");
		}
	}
	else {
		printf("something went wrong opening the file, it mightve been deleted, im now making a new one with reset scores \n");
		std::ofstream myFileWrite("bestEnemy.cmgt");

		for (unsigned int i = 0; i < 5; i++) {
			myFileWrite << "0 ";
		}
		myFileWrite.close();
	}


}

void Enemy::Attack(GenericLabel& label, Character* target)  {
	bool attackingDone = false;
	while(attackingDone == false) {
		attackingDone = animator.HeadButt(.1f);
	}

	int damage;
	if (charged) {
		damage = strength + random(1, 4) - ceilf(target->strength / 2);
	}
	else {
		damage = random(strength + 2, agility * 2) - ceilf(target->strength / 2);
	}


	if (damage <= 0) damage = 1;

	target->health -= damage;

	fitness += damage;

	label.textStr += "\renemy attacks and does " + std::to_string(damage) + " damage\n";

	if(target->CheckDeath()) {
		Enemy* enemyTarget = static_cast<Enemy*>(target);
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
	target->health -= wits;
	damage = wits;

	label.textStr += "\renemy casts magic and does " + std::to_string(damage) + " damage\n";
	if(target->CheckDeath())
		WriteValues(true);}

void Enemy::Tremble(GenericLabel& label) {
	label.textStr += "\renemy trembles in fear...\n";
}

void Enemy::Turn(Character& target) {
	manager.EnemyTurn(&target);
}


bool Enemy::CheckDeath() {
	if (health <= 0) {
		manager.Death();
		return true;
	}
	else {
		return false;
	}
}

void Enemy::WriteValues(bool won) {
	if (won)
		fitness += 10;


	std::ofstream myFileWrite("bestEnemy.csv", std::ios::app); // Append mode

	if (myFileWrite) {
		// Write the 5 chance values to the file
		myFileWrite << attackChance << ","
					<< prepareChance << ","
					<< recoverChance << ","
					<< lowMagicChance << ","
					<< highMagicChance << "," << fitness << "\n";

	} else {
		std::cerr << "Error: Could not open file for writing." << std::endl;
	}
	myFileWrite.close();
	manager.Death();
}