#include "Belladonna.h"
#include "Commentator.h"
#include "Symbols.h"

Belladonna::Belladonna(World* world, Point position, int birth_turn)
	:Plant(OrganismType::BELLADONNA, world, position, birth_turn, STR_BELLADONNA, INITIATIVE_BELLADONNA)
{
	this->symbol = BELLADONNA_SYMBOL;
}

void Belladonna::action()
{
	if (rand() % 100 < 5) Sawing();
}

string Belladonna::organismTypeToString()
{
	return "Belladonna";
}

bool Belladonna::specialActionWhileAttack(Organism* attacker, Organism* victim)
{
	Commentator::addComment(attacker->organismToString() + " ate " + this->organismToString());
	if (attacker->getStrength() >= 99) {
		world->deleteOrganism(this);
		Commentator::addComment(attacker->organismToString() + " destroys Belladonna");
	}
	if (attacker->isAnimal()) {
		world->deleteOrganism(attacker);
		Commentator::addComment(attacker->organismToString() + " dies from Belladonna");
	}
	return true;
}

