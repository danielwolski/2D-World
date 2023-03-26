#include "SosnowskysHogweed.h"
#include "Commentator.h"
#include "Symbols.h"

void Sosnowskys_Hogweed::action()
{
	int pozX = position.getX();
	int pozY = position.getY();
	Organism* temp_organism = nullptr;
	drawAnyPosition(position);
	for (int i = 0; i < 4; i++) {
		if (i == 0 && !isDirectionBlocked(Direction::DOWN_))
			temp_organism = world->whatsOnPosition(Point(pozX, pozY + 1));
		else if (i == 1 && !isDirectionBlocked(Direction::UP_))
			temp_organism = world->whatsOnPosition(Point(pozX, pozY - 1));
		else if (i == 2 && !isDirectionBlocked(Direction::LEFT_))
			temp_organism = world->whatsOnPosition(Point(pozX - 1, pozY));
		else if (i == 3 && !isDirectionBlocked(Direction::RIGHT_))
			temp_organism = world->whatsOnPosition(Point(pozX + 1, pozY));

		if (temp_organism != nullptr && temp_organism->isAnimal()) {
			world->deleteOrganism(temp_organism);
			Commentator::addComment(organismToString() + " kills " + temp_organism->organismToString());
		}
	}
	if (rand() % 100 < 5) Sawing();
}

Sosnowskys_Hogweed::Sosnowskys_Hogweed(World* world, Point position, int birth_turn)
	:Plant(OrganismType::SOSNOWSKYS_HOGWEED, world, position, birth_turn, STR_SOSNOWSKYS_HOGWEED, INITIATIVE_SOSNOWSKYS_HOGWEED)
{
	this->symbol = SOSNOWSKYS_HOGWEED_SYMBOL;
}

string Sosnowskys_Hogweed::organismTypeToString()
{
	return "Sosnowskys Hogweed";
}

bool Sosnowskys_Hogweed::specialActionWhileAttack(Organism* attacker, Organism* victim)
{
	if (attacker->getStrength() >= 10) {
		world->deleteOrganism(this);
		Commentator::addComment(attacker->organismToString() + " ate " + this->organismToString());
	}
	if ((attacker->isAnimal())
		|| attacker->getStrength() < 10) {
		world->deleteOrganism(attacker);
		Commentator::addComment(this->organismToString() + " kills " + attacker->organismToString());
	}
	return true;
}
