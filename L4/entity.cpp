#include "entity.h"
#include "game.h"
#include <ctime>
int entity::durationOfBonuses;
void entity::setPos(PAIR pos) {
	position = pos;
}
void entity::initBonusesDuration() {
	durationOfBonuses = 200000;
}
PAIR entity::getPos() {
	return position;
}
PAIR entity::getSpeed() {
	return speed;
}
void entity::setSpeed(PAIR spd) {
	speed = spd;
}
int entity::takeChance(int n) {
	int ch = (rand() + time(NULL)) % n;;
	return ch;
}
PAIR contact(entity* el1, entity* el2) {
	double xCross, yCross;
	if (el1->getPos().x > el2->getPos().x) {
		std::swap(el1, el2);
	}
	if (el1->getPos().x + el1->getSize().x/2 >= el2->getPos().x - el2->getSize().x/2) {
		xCross = el1->getPos().x + el1->getSize().x/2 - el2->getPos().x - el2->getSize().x/2;
		if (el1->getPos().y > el2->getPos().y) {
			std::swap(el1, el2);
		}
		if (el1->getPos().y + el1->getSize().y/2 >= el2->getPos().y - el2->getSize().y/2) {
			yCross = el1->getPos().y + el1->getSize().y/2 - el2->getPos().y - el2->getSize().y/2;
			return { xCross, yCross };
		}
	}
	return { 0, 0 };
}

void entity::move() {
	position.x += speed.x;
	position.y += speed.y;
	bounceOff();
}

bool entity::alife() {
	if (position.y < 0) {
		return false;
	}
	else {
		return true;
	}
}

void entity::bounceOff() {
	if (position.x + getSize().x / 2 > game::G->getWindowSize().x || position.x - getSize().x / 2 < 0) {
		speed.x *= -1;
	}
	if (position.y + getSize().y / 2 > game::G->getWindowSize().y) {
		speed.y *= -1;
	}
}
