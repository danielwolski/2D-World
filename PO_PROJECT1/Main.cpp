#include <iostream>
#include <ctime>
#include <conio.h>
#include "World.h"
#include "OrganismMaker.h"

using namespace std;

#define SIZE 8

int main()
{
	srand(time(NULL));

	World* world;
	while (true) 
	{
			world = new World(SIZE, SIZE);
			world->generateWorld();
			break;
	}

	while (world->isGameOver() == false) {
		world->drawWorld();
		world->makeTurn();
	}
	delete world;
	return 0;
}