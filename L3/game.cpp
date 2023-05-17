#include "game.h"
#include <GL\freeglut.h>
#include <algorithm>
#include <set>
#include <queue>
#include <iostream>

void Game::draw() {
	for (int x = 0; x < screen_size; x++) {
		for (int y = 0; y < screen_size; y++) {
			if (first_touch == std::pair<int, int>({ x, y }) || second_touch == std::pair<int, int>({ x, y }))
				playing_field[x][y]->draw(x, y, true);
			else {
				playing_field[x][y]->draw(x, y, false);
			}
			
		}
	}
}

void Game::init_game(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Лабораторная 3");

	register_auxiliary_functions();

	glutMainLoop();
}

Game* CurrentInstance;

extern "C"
void renderScene() {
	// очистка буфера цвета и глубины
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	CurrentInstance->mechanics();
	CurrentInstance->draw();
	glutSwapBuffers();
}


void mouseButton(int button, int state, int x, int y) {
	// если нажата левая кнопка
	
	if (button == GLUT_LEFT_BUTTON) {
		// когда кнопка отпущена
		if (state == GLUT_UP && CurrentInstance->to_change.empty()) {
			//std::cout << x << ' ' << y << '\n';
			if (CurrentInstance->first_touch == std::pair<int, int>({-1, -1})) {
				CurrentInstance->first_touch.first = x / 40;
				CurrentInstance->first_touch.second = y / 40;
			}
			else {
				if (CurrentInstance->second_touch == std::pair<int, int>({ -1, -1 })) {
					CurrentInstance->second_touch.first = x / 40;
					CurrentInstance->second_touch.second = y / 40;
				}
			}
		}
	}
}

void Game::register_auxiliary_functions() {
	CurrentInstance = this;
	::glutDisplayFunc(::renderScene);
	::glutIdleFunc(::renderScene);
	::glutMouseFunc(::mouseButton);
}