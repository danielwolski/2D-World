#include "Sheep.h"
#include "Symbols.h"

Sheep::Sheep(World* world, Point position, int birth_turn)
	:Animal(OrganismType::SHEEP, world, position, birth_turn, STR_SHEEP, INITIATIVE_SHEEP)
{
	this->movement_range = MOVE_RANGE_SHEEP;
	this->chance_to_move = CHANCE_TO_MOVE_SHEEP;
	this->symbol = SHEEP_SYMBOL;
}

string Sheep::organismTypeToString()
{
	return "Sheep";
}

Sheep::~Sheep(){}
