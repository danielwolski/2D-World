#pragma once
#include "Animal.h"

#define MOVE_RANGE_ANTELOPE 2
#define CHANCE_TO_MOVE_ANTELOPE 1
#define STR_ANTELOPE 4
#define INITIATIVE_ANTELOPE 4

class Antelope : public Animal
{
public:
	Antelope(World* world, Point position, int birth_turn);
	string organismTypeToString() override;
	bool specialActionWhileAttack(Organism* attacker, Organism* victim) override;
};