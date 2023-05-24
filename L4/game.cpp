#include "game.h"
#include "block.h"
#include <ctime>
#include <GL/freeglut.h>

game* game::G;
void game::create_field() {
	for (double x = 0; x < game::windowSize.x; x += 50) {
		for (double y = game::windowSize.y; y >= game::windowSize.y / 2; y -= 25) {
			int chance = (rand() + time(NULL)) % int((game::windowSize.y - y) / 30 + 1);
			if (chance == 0) {
				block* p = new block({ x + 30.0, y - 15.0 });
			}
		}
	}
}

PAIR game::getWindowSize() {
	return windowSize;
}

game* CurrentInstance;

extern "C"

void game::initGame(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 0);
	glutInitWindowSize(500, 700);
	glutCreateWindow("Арканоид");

	initGlutFunctions();

	glutMainLoop();
}
bool win() {
	bool f = true;
	for (auto blockT : block::existing_blocks) {
		if (blockT->getHP() != absolut) {
			f = false;
			break;
		}
	}
	return f;
}

void game::mechanic() {
	currentTime++;
	if (!ball::exiting_ball && !win()) {
		Sleep(500);
		exit(0);
	}
	block::moveBlocks();
	bonus::moveBonuses();
	ball::exiting_ball->move();
	block::ballHit();
	block::blockHit();
	bonus::carriageHit();
	carriage::ballHit();
}

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double w = glutGet(GLUT_WINDOW_WIDTH);
	double h = glutGet(GLUT_WINDOW_HEIGHT);
	glOrtho(0, w, 0, h, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	CurrentInstance->mechanic();
	block::drawExitingBlocks();
	bonus::drawExitingBonuses();
	ball::exiting_ball->drawBall();
	carriage::exiting_carriage->drawC();
	glutSwapBuffers();
	glutPostRedisplay();
}


void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 27) {
		exit(0);
	}
	if (key == ' ') {
		if (ball::exiting_ball->sticking) {
			ball::exiting_ball->sticking = false;
			//ball::exiting_ball->setSpeed({ 0, ball::exiting_ball->full_speed });
		}
	}
	if (key == 'a' || key == 'A') {
		carriage::exiting_carriage->moveLeft();
	}
	if (key == 'd' || key == 'D') {
		carriage::exiting_carriage->moveRight();
	}

}

void resize(int w, int h) {
	glViewport(0, 0, 500, 700);
}

void game::initGlutFunctions() {
	CurrentInstance = this;
	::glutDisplayFunc(::renderScene);
	::glutIdleFunc(::renderScene);
	::glutKeyboardFunc(::processNormalKeys);
	::glutReshapeFunc(::resize);
}