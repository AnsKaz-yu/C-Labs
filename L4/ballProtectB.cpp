#include "ballProtectB.h"
#include "ball.h"
#include <GL/freeglut.h>
void ballProtectB::activate() {
	ball::exiting_ball->protection = true;
}

void ballProtectB::drawBonus() {
	double pi = 2 * acos(0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.5f, 0.5f);
	for (int i = 0; i < 4; ++i)
		glVertex2f(position.x + radius * cos(2 * pi / 4.0 * i), position.y + radius * sin(2 * pi / 4.0 * i));
	glEnd();
}