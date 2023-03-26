#pragma once
#include <iostream>
#include <vector> 
#include "Organism.h"
#include "Point.h"

using namespace std;

class Organism;
class Human;

class World
{
public:
	World(int sizeX, int sizeY);
	World();
	World(World&& other);
	~World();
	void generateWorld();
	void makeTurn();
	void drawWorld();
	Point drawFreeField();
	bool checkIfFree(Point field);
	Organism* whatsOnPosition(Point field);
	void addOrganism(Organism* organism);
	void deleteOrganism(Organism* organism);

	int getSizeX();
	int getSizeY();
	const int getTurnNumber();
	Organism*** getGrid();
	vector<Organism*> getOrganisms();
	bool getIsHumanAlive();
	void setIsHumanAlive(bool is_player_alive);
	bool isGameOver();
	void setIsGameOver(bool is_game_over);
	Organism* getHuman();
protected:
	int sizeX, sizeY;
	int turn_number;
	Organism*** world_grid;
	bool is_player_alive;
	bool is_game_over;
	vector<Organism*> organisms;
	Human* human;

	void sortOrganisms();
	void manageInput();
};