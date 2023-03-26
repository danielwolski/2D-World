#pragma once
#include "Plant.h"
 
#define STR_SOSNOWSKYS_HOGWEED 10
#define INITIATIVE_SOSNOWSKYS_HOGWEED 0

class Sosnowskys_Hogweed : public Plant
{
public:
	void action() override;
	Sosnowskys_Hogweed(World* world, Point position, int birth_turn);
	string organismTypeToString() override;
	bool specialActionWhileAttack(Organism* attacker, Organism* victim) override;
};

