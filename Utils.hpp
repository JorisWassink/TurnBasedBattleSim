#pragma once
#include <iostream>
#include <math.h>
#include <random>

#include "Character.hpp"

inline int random(int lowest, int highest) {
	if (lowest > highest)
		std::swap(lowest, highest);

	int rando = rand() % ((highest - lowest) + 1) + lowest;
	return rando;
}

inline float randomf(float lowest, float highest) {
	if (lowest > highest) {
		std::swap(lowest, highest);
	}

	std::random_device rd;  // Random number generator
	std::mt19937 gen(rd()); // Mersenne Twister engine
	std::uniform_real_distribution<float> dis(lowest, highest);

	return dis(gen);
}

struct ThreeIntegers {
	int a, b, c;
};

inline Character* FastestCharacter(Character* character1, Character* character2) {
	Character* moreAgile = (character1->agility > character2->agility) ? character1 : character2;
	return moreAgile;
}