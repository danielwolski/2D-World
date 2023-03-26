#include "Animal.h"
#include "Commentator.h"
#include "OrganismMaker.h"

void Animal::action()
{
	for (int i = 0; i < movement_range; i++) {
		Point future_position = move();

		if (world->checkIfFree(future_position)
			&& world->whatsOnPosition(future_position) != this) {
			collision(world->whatsOnPosition(future_position));
			break;
		}
		else if (world->whatsOnPosition(future_position) != this) makeMove(future_position);
	}
}

void Animal::collision(Organism* other)
{
	if (organism_type == other->getOrganismType()) {
		if (rand() % 100 < 50)  breeding(other);
	}

	else {
		if (other->specialActionWhileAttack(this, other)) 
			return;
		if (specialActionWhileAttack(this, other)) 
			return;

		if (str >= other->getStrength()) 
		{
			world->deleteOrganism(other);
			makeMove(other->getPosition());
			Commentator::addComment(organismToString() + " kills " + other->organismToString());
		}
		else 
		{
			world->deleteOrganism(this);
			Commentator::addComment(other->organismToString() + " kills " + organismToString());
		}
	}
}

int Animal::getMoveRange()
{
	return movement_range;
}

void Animal::setMoveRange(int movement_range)
{
	this->movement_range = movement_range;
}

double Animal::getChanceOfMoving()
{
	return chance_to_move;
}

void Animal::setChanceOfMoving(double chance_to_move)
{
	this->chance_to_move = chance_to_move;
}

bool Animal::isAnimal()
{
	return true;
}

Animal::~Animal()
{
}

Animal::Animal(OrganismType organism_type, World* world, Point position, int age, int str, int initiative)
	:Organism(organism_type, world, position, age, str, initiative)
{
	direction = new bool[4]{ true,true,true,true };
	was_breeding = false;
}

Point Animal::move()
{
	if (rand() % 100 >= (int)(chance_to_move * 100)) return position;
	else return drawAnyPosition(position);
}

void Animal::breeding(Organism* other)
{
	if (this->was_breeding || other->getWasBreeding()) 
		return;
	Point tmp1Point = this->drawFreePosition(position);
	if (tmp1Point == position) 
	{
		Point tmp2Point = other->drawFreePosition(other->getPosition());

		if (tmp2Point == other->getPosition()) 
			return;
		else 
		{
			Organism* tmpOrganism = organisms_maker::createNewOrganism(organism_type, this->world, tmp2Point);
			Commentator::addComment("Born " + tmpOrganism->organismToString());
			world->addOrganism(tmpOrganism);
			was_breeding = true;
			other->setWasBreeding(true);
		}
	}
	else 
	{
		Organism* tmpOrganism = organisms_maker::createNewOrganism(organism_type, this->world, tmp1Point);
		Commentator::addComment("Born " + tmpOrganism->organismToString());
		world->addOrganism(tmpOrganism);
		was_breeding = true;
		other->setWasBreeding(true);
	}
}