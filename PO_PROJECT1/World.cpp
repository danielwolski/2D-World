#pragma once
#include "World.h"
#include "Commentator.h"
#include "OrganismMaker.h"
#include "Keys.h"
#include <algorithm>
#include <tuple>
#include <iostream>
#include <fstream>
#include <conio.h>

#define NUMBER_OF_SPECIES 10
#define NUMBER_OF_ANIMALS_AT_THEBEG 2 //number of animals of each kind at the beginning of the game

World::World(int sizeX, int sizeY) {
	// Constructor to initialize World class object
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	turn_number = 0;
	is_player_alive = true;
	organisms.reserve(sizeX * sizeY / 2);

	// Allocate memory for the 2D array of pointers to Organism objects
	world_grid = new Organism * *[sizeY];
	for (int i = 0; i < sizeY; i++) {
		world_grid[i] = new Organism * [sizeX];
	}

	// Initialize the 2D array of pointers to null
	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			world_grid[i][j] = nullptr;
		}
	}
}

World::World()
{
	// Default constructor to initialize World class object
	this->sizeX = 0;
	this->sizeY = 0;
	turn_number = 0;
	is_player_alive = true;
	organisms.reserve(0);
}

World::World(World&& other)
{
	// Move constructor to move the data from one object to another
	// Used to reduce copying overhead
	this->sizeX = other.sizeX;
	this->sizeY = other.sizeY;
	this->turn_number = other.turn_number;
	this->world_grid = other.world_grid;
	this->is_player_alive = other.is_player_alive;
	this->is_game_over = other.is_game_over;
	this->organisms = other.organisms;
	this->human = other.human;

	// Update the pointers of the Organism objects in the organisms vector to point to the new World object
	for (size_t i = 0; i < organisms.size(); i++) {
		organisms[i]->setWorld(this);
	}

	// Reset the other object's data members
	other.sizeX = 0;
	other.sizeY = 0;
	other.turn_number = 0;
	other.world_grid = nullptr;
	other.is_player_alive = false;
	other.is_game_over = false;
	other.human = nullptr;
}

void World::sortOrganisms()
{
	// Sort organisms vector based on the priority of each organism
	sort(organisms.begin(), organisms.end(),
		[](Organism* org1, Organism* org2) {
			int ini1 = org1->getInitiative();
			int ini2 = org2->getInitiative();
			int birth_turn1 = org1->getBirthTurn();
			int birth_turn2 = org2->getBirthTurn();
			return tie(ini2, birth_turn1) < tie(ini1, birth_turn2);
		});
}

World::~World() {
	// Destructor to deallocate memory for the 2D array of pointers to Organism objects
	for (int i = 0; i < sizeY; i++) {
		delete[] world_grid[i];
	}
	delete world_grid;
}

// This function generates the world by creating organisms and placing them on the grid.
void World::generateWorld() {
	Point position = drawFreeField();
	Organism* temp_organism = organisms_maker::createNewOrganism(Organism::OrganismType::HUMAN, this, position);
	addOrganism(temp_organism);
	human = (Human*)temp_organism;

	// The loop creates a set number of each type of organism and places them on the grid.
	for (int i = 0; i < NUMBER_OF_ANIMALS_AT_THEBEG; i++)
	{
		Point position = drawFreeField();

		// If the position is not valid, exit the loop.
		if (!(position == Point(-1, -1))) {
			addOrganism(organisms_maker::createNewOrganism(Organism::OrganismType::WOLF, this, position));
		}
		else return;

		// Repeat for each type of organism.
		position = drawFreeField();
		if (!(position == Point(-1, -1))) {
			addOrganism(organisms_maker::createNewOrganism(Organism::OrganismType::SHEEP, this, position));
		}
		else return;
		position = drawFreeField();
		if (!(position == Point(-1, -1))) {
			addOrganism(organisms_maker::createNewOrganism(Organism::OrganismType::FOX, this, position));
		}
		else return;
		position = drawFreeField();
		if (!(position == Point(-1, -1))) {
			addOrganism(organisms_maker::createNewOrganism(Organism::OrganismType::TURTLE, this, position));
		}
		else return;
		position = drawFreeField();
		if (!(position == Point(-1, -1))) {
			addOrganism(organisms_maker::createNewOrganism(Organism::OrganismType::ANTYLOPA, this, position));
		}
		else return;
		position = drawFreeField();
		if (!(position == Point(-1, -1))) {
			addOrganism(organisms_maker::createNewOrganism(Organism::OrganismType::GRASS, this, position));
		}
		else return;
		position = drawFreeField();
		if (!(position == Point(-1, -1))) {
			addOrganism(organisms_maker::createNewOrganism(Organism::OrganismType::SOW_THISTLE, this, position));
		}
		else return;
		position = drawFreeField();
		if (!(position == Point(-1, -1))) {
			addOrganism(organisms_maker::createNewOrganism(Organism::OrganismType::GUARANA, this, position));
		}
		else return;
		position = drawFreeField();
		if (!(position == Point(-1, -1))) {
			addOrganism(organisms_maker::createNewOrganism(Organism::OrganismType::BELLADONNA, this, position));
		}
		else return;
		position = drawFreeField();
		if (!(position == Point(-1, -1))) {
			addOrganism(organisms_maker::createNewOrganism(Organism::OrganismType::SOSNOWSKYS_HOGWEED, this, position));
		}
		else return;
	}
}

// function to execute one turn in the game
void World::makeTurn()
{
	Commentator::clearComment();
	manageInput();
	if (is_game_over) return; 
	turn_number++; 
	drawWorld();
	sortOrganisms(); // sort organisms based on initiative

	// execute the action of each organism
	for (size_t i = 0; i < organisms.size(); i++) {
		// if the organism is dead, skip it
		if (organisms[i]->getIsDead() == true) { continue; }
		// if the organism was just born, skip it
		else if (organisms[i]->getBirthTurn() != turn_number) {
			organisms[i]->action();
			drawWorld();
		}
	}

	// remove dead organisms from the world and delete them from memory
	for (size_t i = 0; i < organisms.size(); i++) {
		if (organisms[i]->getIsDead() == true) {
			delete organisms[i];
			organisms.erase(organisms.begin() + i);
		}
	}

	// reset the wasBreeding flag of each organism
	for (size_t i = 0; i < organisms.size(); i++) {
		organisms[i]->setWasBreeding(false);
	}
}

// function to draw the world
void World::drawWorld() {
	system("cls"); // clear the console
	cout << "												Daniel Wolski\n";
	cout << "Use arrow keys to move\n";
	cout << "Space - special skill\n";
	cout << "Esc - finish \nEnter - next turn\n\n";

	// draw the top border
	for (int j = 0; j < (2 * sizeX) + 3; j++)
		cout << "#";
	cout << endl;

	// draw each row of the world grid
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < 1; j++)
			cout << "#";

		for (int j = 0; j < sizeX; j++) {
			cout << " ";
			if (world_grid[i][j] == nullptr) cout << " "; // if there is no organism, leave an empty space
			else world_grid[i][j]->drawing(); // draw the organism
		}
		cout << " ";
		for (int j = 0; j < 1; j++)
			cout << "#";
		cout << endl;
	}

	// draw the bottom border
	for (int j = 0; j < (2 * sizeX) + 3; j++)
		cout << "#";
	cout << endl;

	cout << "Turn " << turn_number << endl;
	cout << endl;
	Commentator::comment();
}

int World::getSizeX() {
	return sizeX;
}

int World::getSizeY() {
	return sizeY;
}

const int World::getTurnNumber() {
	return turn_number;
}

bool World::checkIfFree(Point field)
{
	if (world_grid[field.getY()][field.getX()] == nullptr) return false;
	else return true;
}

Organism* World::whatsOnPosition(Point field)
{
	return world_grid[field.getY()][field.getX()];
}

Organism*** World::getGrid()
{
	return world_grid;
}

vector<Organism*> World::getOrganisms()
{
	return organisms;
}

bool World::getIsHumanAlive()
{
	return is_player_alive;
}

void World::setIsHumanAlive(bool is_player_alive)
{
	this->is_player_alive = is_player_alive;
}

bool World::isGameOver()
{
	return is_game_over;
}

void World::setIsGameOver(bool is_game_over)
{
	this->is_game_over = is_game_over;
}

void World::addOrganism(Organism* organism)
{
	// Add the organism to the list of organisms
	organisms.push_back(organism);

	// Add the organism to the world grid at its position
	world_grid[organism->getPosition().getY()][organism->getPosition().getX()] = organism;
}

void World::deleteOrganism(Organism* organism)
{
	// Remove the organism from the world grid at its position
	getGrid()[organism->getPosition().getY()][organism->getPosition().getX()] = nullptr;

	organism->setIsDead(true);

	// If the organism is the player, set is_player_alive to false and remove the reference to the player
	if (organism->getOrganismType() == Organism::OrganismType::HUMAN) {
		is_player_alive = false;
		human = nullptr;
	}
}

void World::manageInput()
{
	while (true) {
		int input;
		input = _getch();
		if (input == IF_ARROWS) {
			if (is_player_alive) {
				input = _getch();
				if (input == UP) {
					human->setDirection(Organism::Direction::UP_);
					break;
				}
				else if (input == DOWN) {
					human->setDirection(Organism::Direction::DOWN_);
					break;
				}
				else if (input == LEFT) {
					human->setDirection(Organism::Direction::LEFT_);
					break;
				}
				else if (input == RIGHT) {
					human->setDirection(Organism::Direction::RIGHT_);
					break;
				}
			}
			else {
				cout << "Human died, you can't move anymore" << endl;
				continue;
			}
		}
		if (is_player_alive && input == SPACE) {
			Human::Skill* temp_skill = human->getSkill();
			if (temp_skill->getCanBeActivated()) {
				temp_skill->activate();
				human->drink();
				break;
			}
			else if (temp_skill->getIsActive()) {
				cout << "Skill has been activated (Turns left: "
					<< temp_skill->getDuration() << " turns)" << endl;
				continue;
			}
			else {
				cout << "Skill can be activated after " << temp_skill->getCooldown() << " turns" << endl;
				continue;
			}
		}
		else if ((!is_player_alive) && input == SPACE) {
			cout << "Human died, you can't move anymore" << endl;
			continue;
		}
		if (input ==  ESC) {
			is_game_over = true;
			break;
		}
		if (input == ENTER) { break; }
		else {
			cout << "Try again" << endl;
			continue;
		}
	}
}

Organism* World::getHuman()
{
	return human;
}

Point World::drawFreeField()
{
	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			if (world_grid[i][j] == nullptr) {
				while (true) {
					int x = rand() % sizeX;
					int y = rand() % sizeY;
					if (world_grid[y][x] == nullptr) 
						return Point(x, y);
				}
			}
		}
	}
	return Point(-1, -1);
}
