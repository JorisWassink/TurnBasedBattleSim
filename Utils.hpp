#pragma once
#include <iostream>
#include "Character.hpp"

inline int random(int lowest, int highest) {
	if (lowest > highest)
		std::swap(lowest, highest);

	int rando = rand() % ((highest - lowest) + 1) + lowest;
	return rando;
}

struct ThreeIntegers {
	int a, b, c;
};

inline Character* FastestCharacter(Character* character1, Character* character2) {
	Character* moreAgile = (character1->agility > character2->agility) ? character1 : character2;
	return moreAgile;
}