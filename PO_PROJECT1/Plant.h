#pragma once
#include "Organism.h"

class Plant : public Organism
{
public:
	virtual void action() override;
	bool isAnimal() override;
	virtual ~Plant();
protected:
	Plant(OrganismType organism_type, World* world, Point position, int birth_turn, int str, int initiative);
	virtual void Sawing();
private:
	void collision(Organism* other) override;
};