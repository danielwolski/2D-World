#pragma once
#include "Animal.h"

#define MOVE_RANGE_FOX 1
#define CHANCE_TO_MOVE_FOX 1
#define STR_FOX 3
#define INITIATIVE_FOX 7

class Fox : public Animal
{
public:
	Fox(World* world, Point position, int birth_turn);
	string organismTypeToString() override;
	~Fox();
protected:
	Point drawAnyPosition(Point position) override;
};