#pragma once
#include "AllClasses.h"

class organisms_maker
{
public:
	static Organism* createNewOrganism(Organism::OrganismType organism_type, World* world, Point position);
};