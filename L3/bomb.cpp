#include "bomb.h"

void bomb::draw(int x, int y, bool frame) {
	box::draw(x, y, frame);
	box::draw_n_gon(x, y, 10);
}

std::set<changing_box> bomb::activate(int x, int y) {
	std::set<changing_box> pr;
	for (int r = 1; r <= radius; r++) {
		for (int u = 0; u <= r; u++) {
			int v = r - u;
			int m[2] = { -1, 1 };
			for (auto i : m) {
				for (auto j : m) {
					pr.insert({ x + u * i, y + v * j, COLOR::Black });
				}
			}
		}
	}
	return pr;
}