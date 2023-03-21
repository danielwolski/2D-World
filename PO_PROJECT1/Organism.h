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
		BARSZCZ_SOSNOWSKIEGO
	};
	enum class Direction
	{
		LEWO,
		PRAWO,
		GORA,
		DOL,
		NO_DIRECTION
	};

	virtual string organism_type_to_string() = 0;
	virtual void action() = 0;
	virtual void collision(Organism* other) = 0;
	virtual void drawing();
	virtual bool special_action_while_attack(Organism* atakujacy, Organism* ofiara);
	virtual bool is_animal() = 0;
	virtual ~Organism();
	string organism_to_string();
	void make_move(Point przyszlaPozycja);
	static OrganismType LosujTyp();// LOSUJE DOWOLNY TYP OPROCZ CZLOWIEKA
	virtual Point draw_any_position(Point position);
	virtual Point draw_free_position(Point position);

	int get_strength();
	void set_strength(int str);
	int get_initiative();
	void set_initiative(int initiative);
	bool GetCzyUmarl();
	void SetCzyUmarl(bool czyUmarl);
	OrganismType get_organism_type();
	void SetTypOrganizmu(OrganismType organism_type);
	Point get_position();
	void SetPozycja(int x, int y);
	int GetTuraUrodzenia();
	void SetTuraUrodzenia(int turaUrodzenia);
	World* getWorld();
	void setWorld(World* world);
	bool get_was_breeding();
	void set_was_breeding(bool was_breeding);
	int GetKolor();
	void SetKolor(int kolor);
	char GetSymbol();
	void SetSymbol(char symbol);
protected:
	int str;
	int initiative;
	int age;
	int kolor;
	char symbol;
	bool czyUmarl;
	bool* direction;
	bool was_breeding;
	World* world;
	Point position;
	OrganismType organism_type;

	Organism(OrganismType organism_type, World* world, Point position, int turaUrodzenia, int str, int initiative);
	void block_direction(Direction direction);
	void OdblokujKierunek(Direction direction);
	void unlock_all_directions();
	void ZablokujWszystkieKierunki();
	bool is_direction_blocked(Direction direction);
private:
	static int iloscStworzonychOrganizmow;
};