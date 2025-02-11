#pragma once
#include "Enemy.hpp"
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
	strength = 1;
	agility = 0;
	wits = 1;

	for (int i = 0; i < 3; i++)
	{
		switch (random(1, 3)) {
		case 1:
			strength++;
			break;
		case 2:
			agility++;
			break;
		case 3:
			wits++;
			break;

		default:
			throw new _exception();
		}
	}

	maxHealth = strength * 3;
	health = maxHealth;
	sanity = wits * 2;
}

void Enemy::
Attack(GenericLabel& label, Player* target) {

	int damage;
	if (charged) {
		damage = strength + random(1, 4) - ceilf(target->strength / 2);
	}
	else {
		damage = random(strength + 2, agility * 2) - ceilf(target->strength / 2);
	}


	if (damage <= 0) damage = 1;

	target->health -= damage;

	label.textStr += "\renemy attacks and does " + std::to_string(damage) + " damage\n";

	target->CheckDeath();
}

void Enemy::Prepare(GenericLabel& label) {
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
	label.textStr += "\renemy recovers " + std::to_string(sanit) + "sanity and " + std::to_string(wits) + " HP!\n";
}

void Enemy::CastMagic(GenericLabel& label, Player* target) {
	int damage;
	target->health -= wits;
	damage = wits;

	label.textStr += "\renemy casts magic and does " + std::to_string(damage) + " damage\n";
	target->CheckDeath();
}

void Enemy::Tremble(GenericLabel& label) {
	label.textStr += "\renemy trembles in fear...\n";
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