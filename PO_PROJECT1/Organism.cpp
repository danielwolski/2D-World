#include "Organism.h"
#define NUMBER_OF_SPECIES 10

void Organism::drawing()
{
	cout << symbol;
}

bool Organism::specialActionWhileAttack(Organism* attacker, Organism* victim)
{
	return false;
}

int Organism::getStrength()
{
	return str;
}

void Organism::setStrength(int str)
{
	this->str = str;
}

int Organism::getInitiative()
{
	return initiative;
}

void Organism::setInitiative(int initiative)
{
	this->initiative = initiative;
}

bool Organism::getIsDead()
{
	return is_dead;
}

void Organism::setIsDead(bool is_dead)
{
	this->is_dead = is_dead;
}

Organism::OrganismType Organism::getOrganismType()
{
	return organism_type;
}

void Organism::setOrganismType(OrganismType organism_type)
{
	this->organism_type = organism_type;
}

Point Organism::getPosition()
{
	return Point(position.getX(), position.getY());
}

void Organism::setPosition(int x, int y)
{
	position.setX(x);
	position.setY(y);
}

int Organism::getBirthTurn()
{
	return age;
}

void Organism::setBirthTurn(int turaUrodzenia)
{
	this->age = turaUrodzenia;
}

World* Organism::getWorld()
{
	return world;
}

void Organism::setWorld(World* world)
{
	this->world = world;
}

Organism::~Organism()
{
	delete[] direction;
}

string Organism::organismToString()
{
	return (organismTypeToString() + " x[" + to_string(position.getX()) + "] y["
		+ to_string(position.getY()) + "] str[" + to_string(str) + "]");
}

Organism::Organism(OrganismType organism_type, World* world, Point position, int birth_turn, int str, int initiative)
{
	this->organism_type = organism_type;
	this->world = world;
	this->position = position;
	this->age = birth_turn;
	this->str = str;
	this->initiative = initiative;
	is_dead = false;
}

void Organism::makeMove(Point future_position)
{
	int x = future_position.getX();
	int y = future_position.getY();
	world->getGrid()[position.getY()][position.getX()] = nullptr;
	world->getGrid()[y][x] = this;
	position.setX(x);
	position.setY(y);
}

Point Organism::drawAnyPosition(Point position)
{
	unlockAllDirections();
	int posX = position.getX();
	int posY = position.getY();
	int sizeX = world->getSizeX();
	int sizeY = world->getSizeY();
	int directions_possible = 0;

	if (posX == 0) blockDirection(Direction::LEFT_);
	else directions_possible++;
	if (posX == sizeX - 1) blockDirection(Direction::RIGHT_);
	else directions_possible++;
	if (posY == 0) blockDirection(Direction::UP_);
	else directions_possible++;
	if (posY == sizeY - 1) blockDirection(Direction::DOWN_);
	else directions_possible++;

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

Point Organism::drawFreePosition(Point position)
{
	unlockAllDirections();
	int posX = position.getX();
	int posY = position.getY();
	int sizeX = world->getSizeX();
	int sizeY = world->getSizeY();
	int directions_possible = 0;

	if (posX == 0) blockDirection(Direction::LEFT_);
	else {
		if (world->checkIfFree(Point(posX - 1, posY)) == false) directions_possible++;
		else blockDirection(Direction::LEFT_);
	}

	if (posX == sizeX - 1) blockDirection(Direction::RIGHT_);
	else {
		if (world->checkIfFree(Point(posX + 1, posY)) == false) directions_possible++;
		else blockDirection(Direction::RIGHT_);
	}

	if (posY == 0) blockDirection(Direction::UP_);
	else {
		if (world->checkIfFree(Point(posX, posY - 1)) == false) directions_possible++;
		else blockDirection(Direction::UP_);
	}

	if (posY == sizeY - 1) blockDirection(Direction::DOWN_);
	else {
		if (world->checkIfFree(Point(posX, posY + 1)) == false) directions_possible++;
		else blockDirection(Direction::DOWN_);
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

char Organism::getSymbol()
{
	return symbol;
}

void Organism::setSymbol(char symbol)
{
	this->symbol = symbol;
}

void Organism::blockDirection(Direction direction)
{
	this->direction[(int)direction] = false;
}

void Organism::unlockDirection(Direction direction)
{
	this->direction[(int)direction] = true;
}

void Organism::unlockAllDirections()
{
	unlockDirection(Direction::LEFT_);
	unlockDirection(Direction::RIGHT_);
	unlockDirection(Direction::UP_);
	unlockDirection(Direction::DOWN_);
}

void Organism::blockAllDirections()
{
	blockDirection(Direction::LEFT_);
	blockDirection(Direction::RIGHT_);
	blockDirection(Direction::UP_);
	blockDirection(Direction::DOWN_);
}

bool Organism::isDirectionBlocked(Direction direction)
{
	return !(this->direction[(int)direction]);
}

bool Organism::getWasBreeding()
{
	return was_breeding;
}

void Organism::setWasBreeding(bool was_breeding)
{
	this->was_breeding = was_breeding;
}
