#include "Fox.h"
#include "Symbols.h"

Fox::Fox(World* world, Point position, int birth_turn)
	:Animal(OrganismType::FOX, world, position, birth_turn, STR_FOX, INITIATIVE_FOX)
{
	this->movement_range = MOVE_RANGE_FOX;
	this->chance_to_move = CHANCE_TO_MOVE_FOX;
	this->symbol = FOX_SYMBOL;
}

string Fox::organismTypeToString()
{
	return "Fox";
}

Point Fox::drawAnyPosition(Point position)
{
	unlockAllDirections();
	int posX = position.getX();
	int posY = position.getY();
	int sizeX = world->getSizeX();
	int sizeY = world->getSizeY();
	int directions_possible = 0;
	Organism* temp_organism;

	if (posX == 0) blockDirection(Direction::LEFT_);
	else {
		temp_organism = world->getGrid()[posY][posX - 1];
		if (temp_organism != nullptr && temp_organism->getStrength() > this->str) {
			blockDirection(Direction::LEFT_);
		}
		else directions_possible++;
	}

	if (posX == sizeX - 1) blockDirection(Direction::RIGHT_);
	else {
		temp_organism = world->getGrid()[posY][posX + 1];
		if (temp_organism != nullptr && temp_organism->getStrength() > this->str) {
			blockDirection(Direction::RIGHT_);
		}
		else directions_possible++;
	}

	if (posY == 0) blockDirection(Direction::UP_);
	else {
		temp_organism = world->getGrid()[posY - 1][posX];
		if (temp_organism != nullptr && temp_organism->getStrength() > this->str) {
			blockDirection(Direction::UP_);
		}
		else directions_possible++;
	}

	if (posY == sizeY - 1) blockDirection(Direction::DOWN_);
	else {
		temp_organism = world->getGrid()[posY + 1][posX];
		if (temp_organism != nullptr && temp_organism->getStrength() > this->str) {
			blockDirection(Direction::DOWN_);
		}
		else directions_possible++;
	}

	if (directions_possible == 0) return Point(posX, posY);
	while (true) {
		int temp_draw = rand() % 100;

		if (temp_draw < 25 && !isDirectionBlocked(Direction::LEFT_))
			return Point(posX - 1, posY);

		else if (temp_draw >= 25 && temp_draw < 50 && !isDirectionBlocked(Direction::RIGHT_))
			return Point(posX + 1, posY);

		else if (temp_draw >= 50 && temp_draw < 75 && !isDirectionBlocked(Direction::UP_))
			return Point(posX, posY - 1);

		else if (temp_draw >= 75 && !isDirectionBlocked(Direction::DOWN_))
			return Point(posX, posY + 1);
	}
}

Fox::~Fox()
{
}