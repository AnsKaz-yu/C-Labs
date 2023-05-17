#include <GL/freeglut.h>
#include <iostream>
#include "box.h"


void box::draw_n_gon(int x, int y, int n) const {

	double pi = 2 * acos(0.0);
	double rad = (0.9 / screen_size);
	double X = (double)(x + 0.5) * 2 / screen_size - 1.0;
	double Y = 1.0 - (double)(y + 0.5) * 2 / screen_size;

	glBegin(GL_POLYGON); // Рисуем правильную n-стороннюю форму
	glColor3f(0.9f, 0.9f, 0.9f);
	for (int i = 0; i < n; ++i)
		glVertex2f(X + rad * cos(2 * pi / n * i), Y + rad * sin(2 * pi / n * i));
	glEnd();
}

void box::set_color() const{
	switch (color) {
	case COLOR::Blue:
		glColor3f(0.0f, 0.0f, 1.0f);
		break;
	case COLOR::Green:
		glColor3f(0.0f, 1.0f, 0.0f);//Green
		break;
	case COLOR::Purple:
		glColor4f(1.0f, 0.0f, 1.0f, 0.0f);//purple
		break;
	case COLOR::Red:
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
		break;
	case COLOR::Yellow:
		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);//yellow
		break;
	case COLOR::Light_blue:
		glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
		break;
	case COLOR::Orange:
		glColor3f(1.0f, 0.5f, 0.0f);
		break;
	case COLOR::Brown:
		glColor4f(1.0f, 0.5f, 0.5f, 0.0f);
		break;
	case COLOR::Dark_grey:
		glColor3f(0.3f, 0.3f, 0.3f);
		break;
	case COLOR::Black:
		glColor3f(0.0f, 0.0f, 0.0f);//Black
		break;
	}
	
}

void box::draw(int x, int y, bool frame) {
	//рисуем прямоугольник
	double xl, xr;
	double yu, yd;

	//преобразуем игровые координаты в координаты экрана для рисования
	xl = (double)(x) / screen_size * 2 - 1;
	xr = (double)(x + 1) / screen_size * 2 - 1;
	
	yu = 1.0 - (double)y / screen_size * 2;
	yd = 1.0 - (double)(y + 1) / screen_size * 2;
	
	

	if (frame) {
		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f(xl, yu);
		glVertex2f(xl, yd);
		glVertex2f(xr, yd);
		glVertex2f(xr, yu);
		glEnd();
	}
	
	glBegin(GL_QUADS);
	set_color();
	xl += 0.01;
	xr -= 0.01;
	yd += 0.01;
	yu -= 0.01;
	
	

	glVertex2f(xl, yu);
	glVertex2f(xl, yd);
	glVertex2f(xr, yd);
	glVertex2f(xr, yu);

	glEnd();
}

std::set<changing_box> box::activate(int x, int y) {
	std::set<changing_box> pr;
	return pr;
}

