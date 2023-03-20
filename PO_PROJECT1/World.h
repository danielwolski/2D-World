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
	void generate_world(/*double zapelnienieSwiatu*/);
	void makeTurn();
	void drawWorld();
	Point WylosujWolnePole();
	bool check_if_free(Point pole);
	Organism* whats_on_pos(Point pole);
	void add_organism(Organism* organism);
	void delete_organism(Organism* organism);

	int GetSizeX();
	int GetSizeY();
	const int GetNumerTury();
	Organism*** get_grid();
	vector<Organism*> getOrganisms();
	bool GetCzyCzlowiekZyje();
	void SetCzyCzlowiekZyje(bool is_player_alive);
	bool is_game_over();
	void SetCzyJestKoniecGry(bool czyJestKoniecGry);
	Organism* GetCzlowiek();
protected:
	int sizeX, sizeY;
	int turn_number;
	Organism*** world_grid;
	bool is_player_alive;
	bool czyJestKoniecGry;
	vector<Organism*> organisms;
	Human* czlowiek;

	void sortOrganisms();
	void ObslugaInputu();
};