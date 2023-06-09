#include "OrganismMaker.h"

Organism* organisms_maker::createNewOrganism(Organism::OrganismType organism_type, World* world, Point position)
{
	switch (organism_type) {
	case Organism::OrganismType::WOLF: return new Wolf(world, position, world->getTurnNumber());
	case Organism::OrganismType::SHEEP: return new Sheep(world, position, world->getTurnNumber());
	case Organism::OrganismType::FOX: return new Fox(world, position, world->getTurnNumber());
	case Organism::OrganismType::TURTLE: return new Turtle(world, position, world->getTurnNumber());
	case Organism::OrganismType::ANTYLOPA: return new Antelope(world, position, world->getTurnNumber());
	case Organism::OrganismType::HUMAN: return new Human(world, position, world->getTurnNumber());
	case Organism::OrganismType::GRASS: return  new Grass(world, position, world->getTurnNumber());
	case Organism::OrganismType::SOW_THISTLE: return  new Sow_Thistle(world, position, world->getTurnNumber());
	case Organism::OrganismType::GUARANA: return  new Guarana(world, position, world->getTurnNumber());
	case Organism::OrganismType::BELLADONNA: return  new Belladonna(world, position, world->getTurnNumber());
	case Organism::OrganismType::SOSNOWSKYS_HOGWEED: return  new Sosnowskys_Hogweed(world, position, world->getTurnNumber());
	default: return nullptr;
	}
}