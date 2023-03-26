#include "Grass.h"
#include "Symbols.h"

Grass::Grass(World* world, Point position, int birth_turn)
	:Plant(OrganismType::GRASS, world, position, birth_turn, STR_GRASS, INITIATIVE_GRASS)
{
	this->symbol = GRASS_SYMBOL;
}

string Grass::organismTypeToString()
{
	return "Grass";
}
