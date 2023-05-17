#include "bonus.h"
void bonus::draw(int x, int y, bool frame) {
	box::draw(x, y, frame);
	box::draw_n_gon(x, y, 3);
}

void bonus::mixing() {
	for (int i = 0; i < 4; i++) {
		std::swap(options[i], options[create_rand(4)]);
	}
}

std::set<changing_box> bonus::activate(int x, int y) {
	mixing();
	std::set<changing_box> pr;
	for (int i = 0; i < 2; i++) {
		pr.insert({ x + options[i][0], y + options[i][1], this->get_color() });
	}
	return pr;
}