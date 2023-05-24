#include "bonus.h"
#include "carriage.h"
#include <GL/freeglut.h>
std::set<bonus*> bonus::exiting_bonuses;
double bonus::radius;
void bonus::drawExitingBonuses() {
	for (auto bonusT : exiting_bonuses) {
		bonusT->drawBonus();
	}
}
PAIR bonus::getSize() {
	return { radius * 2, radius * 2 };
}
void bonus::setRadius(double r) {
	radius = r;
}

void bonus::carriageHit() {
	bonus* to_delete = NULL;
	for (auto bonusT : exiting_bonuses) {
		if (to_delete) {
			delete to_delete;
			to_delete = NULL;
		}
		PAIR c = contact(bonusT, carriage::exiting_carriage);
		if (c != EMPTY_PAIR) {
			bonusT->activate();
			to_delete = bonusT;
		}
	}
	if (to_delete) {
		delete to_delete;
		to_delete = NULL;
	}
}

void bonus::moveBonuses() {
	bonus* to_delete = NULL;
	for (auto bonusT : exiting_bonuses) {
		if (to_delete) {
			delete to_delete;
			to_delete = NULL;
		}
		bonusT->move();
		if (!bonusT->alife()) {
			to_delete = bonusT;
		}
	}
	if (to_delete) {
		delete to_delete;
		to_delete = NULL;
	}
}