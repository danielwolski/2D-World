#include "Plant.h"
#include "OrganismMaker.h"

void Plant::action()
{
	if (rand() % 100 < 30) Sawing();
}

void Plant::collision(Organism* other) {}

bool Plant::isAnimal()
{
	return false;
}

Plant::Plant(OrganismType organism_type, World* world, Point position, int birth_turn, int strength, int initiative)
	:Organism(organism_type, world, position, birth_turn, strength, initiative)
{
	direction = new bool[4]{ true,true,true,true };
}

void Plant::Sawing()
{
	Point temp_pos = this->drawFreePosition(position);
	if (temp_pos == position) return;
	else {
		Organism* temp_organism = organisms_maker::createNewOrganism(organism_type, this->world, temp_pos);
		Commentator::addComment("New plant grows " + temp_organism->organismToString());
		world->addOrganism(temp_organism);
	}
}

Plant::~Plant() {}
