#include "ballSpeedB.h"
#include <GL/freeglut.h>
#include "ball.h"
#include "game.h"
void ballSpeedB::activate() {
	ball::exiting_ball->changeSpeedT = game::G->currentTime;
}

void ballSpeedB::drawBonus() {
	double pi = 2 * acos(0.0);
	glBegin(GL_POLYGON);
	glColor3f(2.0f, 0.5f, 1.0f);
	for (int i = 0; i < 5; ++i)
		glVertex2f(position.x + radius * cos(2 * pi / 5.0 * i), position.y + radius * sin(2 * pi / 5.0 * i));
	glEnd();
}