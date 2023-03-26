#pragma once
#include "Plant.h"

#define STR_BELLADONNA 99
#define INITIATIVE_BELLADONNA 0

class Belladonna : public Plant
{
public:
	Belladonna(World* world, Point position, int birth_turn);
	void action() override;
	string organismTypeToString() override;
	bool specialActionWhileAttack(Organism* attacker, Organism* victim) override;
};