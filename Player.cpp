#pragma once
#include "Player.hpp"
#include <filesystem>
#include "Enemy.hpp"
#include "EnemyManager.hpp"
#include <math.h>



Player::Player(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Texture &texture) : Character(
	position, size, color, texture)
{
	Initialize(position, size, color);
}

void Player::Initialize(sf::Vector2f position, sf::Vector2f size, sf::Color color) {
	health = strength * 3;
	maxHealth = health;
	sanity = wits * 2;
	charged = false;

}

Player::~Player() = default;

void Player::update() {}

void Player::SetStats(ThreeIntegers stats) {
	strength = stats.a;
	agility = stats.b;
	wits = stats.c;

	health = strength * 3;
	maxHealth = health;
	sanity = wits * 2;
}

void Player::PlayerTurn() {
	playerTurn = true;
}


void Player::Attack(Enemy* target) {
	int damage;
	if (charged) {
		damage = strength + random(1, 4) - ceilf(target->strength / 2);
	}
	else {
		damage = random(strength + 2, agility * 2) - ceilf(target->strength / 2);
	}

	
	if (damage <= 0) damage = 1;

	target->health -= damage;
	if (target->CheckDeath() == true) {
		pScore++;
	}

	

	playerTurn = false;
	target->manager.PlayerActionResponse(ATTACK, strength);
	target->manager.EnemyTurn(this);
}

void Player::Recover(Enemy* target) {
	int healing = 0;
	int sanit = 0;
	if (random(1, 100) > (ceilf(wits * 1.5) * 11)) {
		healing += random(0,3);
		sanit += random(1,2);
		health += healing;
		sanity += sanit;
	}
	
	
	playerTurn = false;
	target->manager.PlayerActionResponse(RECOVER, healing, sanit);
	target->manager.EnemyTurn(this);
}

void Player::Prepare(Enemy* target) {
	charged = true;
	playerTurn = false;
	target->manager.PlayerActionResponse(PREPARE);
	target->manager.EnemyTurn(this);
}

void Player::Magic(Enemy* target) {
	int damage;
	target->health -= wits;
	damage = wits;
	if (charged) {
		target->health -= strength;
		damage += strength;
	}
	if (target->CheckDeath() == true) {
		pScore++;
	}
	charged = false;
	playerTurn = false;
	target->manager.PlayerActionResponse(MAGIC, damage);
	target->manager.EnemyTurn(this);
}

void Player::Dodge(Enemy* target) {
	int damage;
	int chance = random(0,100);
	if (chance > agility * 10) {
		damage = 1;
	}
	else {
		damage = 0;
	}
	charged = false;
	target->manager.PlayerActionResponse(DODGE, damage);
}


