#include "ballStickingB.h"
#include "carriage.h"
#include <GL/freeglut.h>

void ballStickingB::activate() {
	carriage::exiting_carriage->stickR = true;
}

void ballStickingB::drawBonus() {
	double pi = 2 * acos(0.0);
	glBegin(GL_POLYGON);
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
	for (int i = 0; i < 3; ++i)
		glVertex2f(position.x + radius * cos(2 * pi / 3.0 * i), position.y + radius * sin(2 * pi / 3.0 * i));
	glEnd();
}