#pragma once
#include "Animal.h"

#define MOVE_RANGE_HUMAN 1
#define CHANCE_TO_MOVE_HUMAN 1
#define STR_HUMAN 5
#define INITIATIVE_HUMAN 4

class Human : public Animal
{
public:
	Human(World* world, Point position, int birth_turn);
	~Human();
	void action() override;
	string organismTypeToString() override;

	class Skill
	{
	public:
		Skill();
		void check_condition();
		void activate();
		void deactivate();

		bool getIsActive();
		void setIsActive(bool is_active);
		bool getCanBeActivated();
		void setCanBeActivated(bool can_be_activated);
		int getDuration();
		void setDuration(int duration);
		int getCooldown();
		void setCooldown(int cooldown);

	protected:
		bool can_be_activated;
		bool is_active;
		int duration;
		int cooldown;
	};

	Direction getDirection();
	void setDirection(Direction moveDirection);
	Skill* getSkill();
	void drink();

protected:
	Direction moveDirection;
	Skill* skill;
	Point move() override;
	void magicalPotion();
};