#include "Turtle.h"
#include "Commentator.h"
#include "Symbols.h"

Turtle::Turtle(World* world, Point position, int birth_turn)
	:Animal(OrganismType::TURTLE, world, position, birth_turn, STR_TURTLE, INITIATIVE_TURTLE)
{
	this->movement_range = MOVE_RANGE_TURTLE;
	this->chance_to_move = CHANCE_TO_MOVE_TURTLE;
	this->symbol = TURTLE_SYMBOL;
}

string Turtle::organismTypeToString()
{
	return "Turtle";
}

bool Turtle::specialActionWhileAttack(Organism* attacker, Organism* victim)
{
	if (this == victim) {
		if (attacker->getStrength() < 5 && attacker->isAnimal()) {
			Commentator::addComment(organismToString() + " defends himself from " + attacker->organismToString() + " attack");
			return true;
		}
		else return false;
	}
	else if (this == attacker) {
		if (attacker->getStrength() >= victim->getStrength()) return false;
		else {
			if (victim->getStrength() < 5 && victim->isAnimal()) {
				Commentator::addComment(organismToString() + " defends himself from " + victim->organismToString() + " attack");
				return true;
			}
			else return false;
		}
	}
}