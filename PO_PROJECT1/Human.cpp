#include "Human.h"
#include "Commentator.h"
#include "Symbols.h"

#define SKILL_DURATION 10
#define MAGICAL_POTION_STR_BOOST 10
#define SKILL_COOLDOWN 15

Human::Human(World* world, Point position, int birth_turn)
	:Animal(OrganismType::HUMAN, world, position, birth_turn, STR_HUMAN, INITIATIVE_HUMAN)
{
	this->movement_range = MOVE_RANGE_HUMAN;
	this->chance_to_move = CHANCE_TO_MOVE_HUMAN;
	skill = new Skill();
	moveDirection = Direction::NO_DIRECTION;
	this->symbol = HUMAN_SYMBOL;
}

void Human::action()
{
	if (skill->getIsActive()) {
		Commentator::addComment(organismToString() + " Magical Potion is active: (Turns left: " + to_string(skill->getDuration()) + ")");
		Commentator::comment();
	}

	for (int i = 0; i < movement_range; i++) {
		Point position = move();


		if (world->checkIfFree(position) && world->whatsOnPosition(position) != this) 
		{
			collision(world->whatsOnPosition(position));
			if (skill->getIsActive())
				magicalPotion();
			break;
		}
		else if (world->whatsOnPosition(position) != this) 
			makeMove(position);

		if (skill->getIsActive()) 
			magicalPotion();
	}
	moveDirection = Direction::NO_DIRECTION;
	skill->check_condition();
}

string Human::organismTypeToString()
{
	return "Human";
}

Organism::Direction Human::getDirection()
{
	return moveDirection;
}

void Human::setDirection(Direction moveDirection)
{
	this->moveDirection = moveDirection;
}

Human::Skill* Human::getSkill()
{
	return skill;
}

Point Human::move()
{
	int x = position.getX();
	int y = position.getY();
	drawAnyPosition(position);
	if (isDirectionBlocked(moveDirection)) return position;
	else {
		Point position;
		if (moveDirection == Direction::DOWN_) return Point(x, y + 1);
		else if (moveDirection == Direction::UP_) return Point(x, y - 1);
		else if (moveDirection == Direction::LEFT_) return Point(x - 1, y);
		else if (moveDirection == Direction::RIGHT_) return Point(x + 1, y);
		else return Point(x, y);
	}
}

void Human::magicalPotion()
{
		Human::str--;
}

Human::Skill::Skill()
{
	cooldown = 0;
	duration = 0;
	is_active = false;
	can_be_activated = true;
}

bool Human::Skill::getIsActive()
{
	return is_active;
}

void Human::Skill::setIsActive(bool is_active)
{
	this->is_active = is_active;
}

bool Human::Skill::getCanBeActivated()
{
	return can_be_activated;
}

void Human::Skill::setCanBeActivated(bool can_be_activated)
{
	this->can_be_activated = can_be_activated;
}

int Human::Skill::getDuration()
{
	return duration;
}

void Human::Skill::setDuration(int duration)
{
	this->duration = duration;
}

int Human::Skill::getCooldown()
{
	return cooldown;
}

void Human::Skill::setCooldown(int cooldown)
{
	this->cooldown = cooldown;
}

void Human::Skill::check_condition()
{
	if (cooldown > 0) 
		cooldown--;

	if (duration > 0) 
		duration--;

	if (duration == 0) 
		deactivate();

	if (cooldown == 0) 
		can_be_activated = true;
}

void Human::Skill::activate()
{
	if (cooldown == 0) 
	{
		is_active = true;
		can_be_activated = false;
		cooldown = SKILL_COOLDOWN;
		duration = SKILL_DURATION;
	}
	else if (cooldown > 0)
		cout << "You will be able to drink Magic Potion after" << cooldown << " turns" << endl;
}

void Human::drink()
{
	Human::str = Human::str + MAGICAL_POTION_STR_BOOST;
}

void Human::Skill::deactivate()
{
	is_active = false;
}

Human::~Human() 
{
}
