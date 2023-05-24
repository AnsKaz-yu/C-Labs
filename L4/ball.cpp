#include "ball.h"
#include "game.h"
#include <GL/freeglut.h>
ball* ball::exiting_ball;

PAIR ball::getSize() {
	return { radius * 2, radius * 2 };
}

void ball::move() {
	if (sticking) {
		PAIR getP = carriage::exiting_carriage->getPos();
		//std::cout << "C: " << getP.x << ' ' << getP.y << '\n';
		setPos({ getP.x, getP.y + carriage::exiting_carriage->getSize().y / 2.0 + radius });
		return;
	}
	if (game::G->currentTime - changeSpeedT < durationOfBonuses) {
		position.x += speed.x * 1.5;
		position.y += speed.y * 1.5;
	}
	else {
		position.x += speed.x;
		position.y += speed.y;
	}
	bounceOff();


	if (position.y - radius < 0) {
		if (protection) {
			speed.y *= -1;
			protection = false;
		}
		else {
			delete this;
			Sleep(500);
			exit(0);
		}
	}
}

void ball::drawBall() {
	double pi = 2 * acos(0.0);
	//std::cout << position.x << ' ' << position.y << '\n';
	glBegin(GL_POLYGON); 
	glColor3f(0.9f, 0.9f, 0.9f);
	for (int i = 0; i < 50; ++i)
		glVertex2f(position.x + radius * cos(2 * pi / 50.0 * i), position.y + radius * sin(2 * pi / 50.0 * i));
	glEnd();

	if (protection) {
		glBegin(GL_QUADS);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(0, 0);
		glVertex2f(0, 10);
		glVertex2f(game::G->getWindowSize().x, 10);
		glVertex2f(game::G->getWindowSize().x, 0);
		glEnd();
	}
}

void ball::bounceOffEntity(PAIR cont, entity* v) {
	if (sticking) return;
	position.x -= speed.x;
	position.y -= speed.y;
	double offset = (takeChance(3) - 1);
	double pi = cos(0.0);
	if (cont.x < cont.y) {
		double alpha = (this->getPos().x - v->getPos().x) * 120 / v->getSize().x + offset;
		double sy = full_speed * cos(alpha * pi / 180);
		double sx = (-1) * full_speed * sin(alpha * pi / 180);
		this->setSpeed({ sx, sy });
	}
	else {
		double alpha = (this->getPos().y - v->getPos().y) * 120 / v->getSize().y + offset;
		double sy = full_speed * sin(alpha * pi / 180);
		double sx = (-1) * full_speed * cos(alpha * pi / 180);
		this->setSpeed({ sx, sy });
	}
	move();
}