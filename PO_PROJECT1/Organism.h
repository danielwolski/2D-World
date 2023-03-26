#pragma once
#include <string>
#include "World.h"
#include "Point.h"

using namespace std;

class World;
class Point;

class Organism
{
public:
	enum class OrganismType
	{
		HUMAN,
		WOLF,
		SHEEP,
		FOX,
		TURTLE,
		ANTYLOPA,
		GRASS,
		SOW_THISTLE,
		GUARANA,
		BELLADONNA,
		SOSNOWSKYS_HOGWEED
	};
	enum class Direction
	{
		LEFT_,
		RIGHT_,
		UP_,
		DOWN_,
		NO_DIRECTION
	};

	virtual string organismTypeToString() = 0;
	virtual void action() = 0;
	virtual void collision(Organism* other) = 0;
	virtual void drawing();
	virtual bool specialActionWhileAttack(Organism* attacker, Organism* victim);
	virtual bool isAnimal() = 0;
	virtual ~Organism();
	string organismToString();
	void makeMove(Point future_position);
	virtual Point drawAnyPosition(Point position);
	virtual Point drawFreePosition(Point position);

	int getStrength();
	void setStrength(int str);
	int getInitiative();
	void setInitiative(int initiative);
	bool getIsDead();
	void setIsDead(bool is_dead);
	OrganismType getOrganismType();
	void setOrganismType(OrganismType organism_type);
	Point getPosition();
	void setPosition(int x, int y);
	int getBirthTurn();
	void setBirthTurn(int birth_turn);
	World* getWorld();
	void setWorld(World* world);
	bool getWasBreeding();
	void setWasBreeding(bool was_breeding);
	char getSymbol();
	void setSymbol(char symbol);
protected:
	int str;
	int initiative;
	int age;
	char symbol;
	bool is_dead;
	bool* direction;
	bool was_breeding;
	World* world;
	Point position;
	OrganismType organism_type;

	Organism(OrganismType organism_type, World* world, Point position, int birth_turn, int strength, int initiative);
	void blockDirection(Direction direction);
	void unlockDirection(Direction direction);
	void unlockAllDirections();
	void blockAllDirections();
	bool isDirectionBlocked(Direction direction);
};