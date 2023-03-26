#pragma once
#include "Organism.h"

class Animal : public Organism
{
public:
	virtual void action() override;
	virtual void collision(Organism* other) override;
	bool isAnimal() override;
	virtual ~Animal();

	int getMoveRange();
	void setMoveRange(int movement_range);
	double getChanceOfMoving();
	void setChanceOfMoving(double chance_to_move);
protected:
	int movement_range;
	double chance_to_move;

	Animal(OrganismType organism_type, World* world, Point position, int birth_turn, int str, int initiative);
	virtual Point move();
	virtual void breeding(Organism* other);
};