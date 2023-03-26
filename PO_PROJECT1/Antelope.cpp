#include "Antelope.h"
#include "Commentator.h"
#include "Symbols.h"


Antelope::Antelope(World* world, Point position, int birth_turn)
	:Animal(OrganismType::ANTYLOPA, world, position, birth_turn, STR_ANTELOPE, INITIATIVE_ANTELOPE)
{
	this->movement_range = MOVE_RANGE_ANTELOPE;
	this->chance_to_move = CHANCE_TO_MOVE_ANTELOPE;
	this->symbol = ANTELOPE_SYMBOL;
}

string Antelope::organismTypeToString()
{
	return "Antelope";
}

bool Antelope::specialActionWhileAttack(Organism* attacker, Organism* victim)
{
	if (rand() % 100 < 50) {
		if (this == attacker) {
			Commentator::addComment(organismToString() + " runs away from " + victim->organismToString());
			makeMove(drawFreePosition(victim->getPosition()));
		}
		else if (this == victim) {
			Commentator::addComment(organismToString() + " runs away from " + attacker->organismToString());
			Point temp_position = this->position;
			makeMove(drawFreePosition(this->position));
			if (position == temp_position) {
				world->deleteOrganism(this);
				Commentator::addComment(attacker->organismToString() + " kills " + organismToString());
			}
			attacker->makeMove(temp_position);
		}
		return true;
	}
	else return false;
}