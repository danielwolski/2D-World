#include "Guarana.h"
#include "Commentator.h"
#include "Symbols.h"

Guarana::Guarana(World* world, Point position, int birth_turn)
	:Plant(OrganismType::GUARANA, world, position, birth_turn, STR_GUARANA, INITIATIVE_GUARANA)
{
	this->symbol = GUARANA_SYMBOL;
}

string Guarana::organismTypeToString()
{
	return "Guarana";
}

bool Guarana::specialActionWhileAttack(Organism* attacker, Organism* victim)
{
	Point tmpPosition = this->position;
	world->deleteOrganism(this);
	attacker->makeMove(tmpPosition);
	Commentator::addComment(attacker->organismToString() + " ate " + this->organismToString()
		+ "  and increased strength by  " + to_string(STR_INCREASE));
	attacker->setStrength(attacker->getStrength() + STR_INCREASE);
	return true;
}
