#include "carriageSizeB.h"
#include "carriage.h"
#include "game.h"
#include <GL/freeglut.h>
void carriageSizeB::activate() {
	carriage::exiting_carriage->changeSizeT = game::G->currentTime;
}

void carriageSizeB::drawBonus() {
	double pi = 2 * acos(0.0);
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.5f, 0.0f);
	for (int i = 0; i < 6; ++i)
		glVertex2f(position.x + radius * cos(2 * pi / 6.0 * i), position.y + radius * sin(2 * pi / 6.0 * i));
	glEnd();
}