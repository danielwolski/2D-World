#pragma once
#include "Animal.h"

#define MOVE_RANGE_TURTLE 1
#define CHANCE_TO_MOVE_TURTLE 0.25
#define STR_TURTLE 2
#define INITIATIVE_TURTLE 1

class Turtle : public Animal
{
public:
	Turtle(World* world, Point position, int birth_turn);
	string organismTypeToString() override;
	bool specialActionWhileAttack(Organism* attacker, Organism* victim) override;
};