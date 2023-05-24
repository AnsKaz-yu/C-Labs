#include "carriage.h"
#include "ball.h"
#include "game.h"
#include <GL/freeglut.h>
carriage* carriage::exiting_carriage;
void carriage::moveLeft() {
	if (position.x - size.x/2 > 0)
		position.x -= fullSpeed;
}
void carriage::moveRight() {
	if (position.x + size.x < game::G->getWindowSize().x + size.x/2)
		position.x += fullSpeed;
}
PAIR carriage::getSize() {
	if (game::G->currentTime - changeSizeT < durationOfBonuses) {
		return { size.x * 2, size.y * 2 };
	}
	return size;
}
void carriage::ballHit() {
	PAIR c = contact(ball::exiting_ball, exiting_carriage);
	if (c != EMPTY_PAIR) {
		if (carriage::exiting_carriage->stickR) {
			carriage::exiting_carriage->stickR = false;
			ball::exiting_ball->sticking = true;
			ball::exiting_ball->setSpeed({ 0.0, 0.0 });
		}
		else {
			ball::exiting_ball->bounceOffEntity(c, exiting_carriage);
		}
	}
}
void carriage::drawC() {
	glBegin(GL_QUADS);
	glColor3f(0.4f, 0.4f, 0.0f);
	if (game::G->currentTime - changeSizeT < durationOfBonuses) {
		glVertex2f(position.x - size.x, position.y - size.y / 2);
		glVertex2f(position.x - size.x, position.y + size.y / 2);
		glVertex2f(position.x + size.x, position.y + size.y / 2);
		glVertex2f(position.x + size.x, position.y - size.y / 2);
	}
	else {
		glVertex2f(position.x - size.x / 2, position.y - size.y / 2);
		glVertex2f(position.x - size.x / 2, position.y + size.y / 2);
		glVertex2f(position.x + size.x / 2, position.y + size.y / 2);
		glVertex2f(position.x + size.x / 2, position.y - size.y / 2);
	}
	
	glEnd();
}