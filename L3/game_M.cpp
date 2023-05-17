#include "game.h"
#include <queue>
#define X first
#define Y second

box* Game::create_new_box() {
	box* pr;
	int probability = (rand() + time(NULL))%100;

	if (probability < 3) {
		pr = new bomb;
		return pr;
	}
	if (probability < 6) {
		pr = new bonus;
		return pr;
	}

	pr = new box;
	return pr;
}

void Game::check_connect() {
	for (int x = 0; x < screen_size; x++) {
		for (int y = 0; y < screen_size; y++) {
			if (to_change.find({ x, y, COLOR::Black }) == to_change.end())
				find_connect_comp({ x, y, playing_field[x][y]->get_color() });
		}
	}
}

void Game::make_new() {
	for (int x = 0; x < screen_size; x++) {
		for (int y = 0; y < screen_size; y++) {
			if (playing_field[x][y]->get_color() == COLOR::Black) {
				box* p = create_new_box();
				std::swap(p, playing_field[x][y]);
				delete p;
			}
		}
	}
}

void Game::gravity() {
	for (int x = 0; x < screen_size; x++) {
		for (int y = screen_size - 2; y >= 0; y--) {
			if (playing_field[x][y]->get_color() != COLOR::Black) {
				int yt = y;
				while (yt + 1 < screen_size && playing_field[x][yt + 1]->get_color() == COLOR::Black) {
					std::swap(playing_field[x][yt], playing_field[x][yt + 1]);
					yt++;
				}
			}
			
		}
	}
}

bool Game::existance(std::pair<int, int> u) {
	if (u.X >= screen_size || u.X < 0) return false;
	if (u.Y >= screen_size || u.Y < 0) return false;
	return true;
}

void Game::find_connect_comp(changing_box t) {
	std::set<changing_box> pos;
	std::queue<std::pair<int, int>> q;
	COLOR c = t.color;
	q.push({ t.x, t.y });
	while (!q.empty()) {
		std::pair<int, int> tt = q.front();
		
		q.pop();

		if (!existance(tt)) continue;
		t = { tt.X, tt.Y, playing_field[tt.X][tt.Y]->get_color() };

		if (t.color != c) continue;
		int s = pos.size();
		pos.insert({ t.x, t.y, COLOR::Black });
		if (s == pos.size()) continue;

		q.push({ t.x + 1, t.y});
		q.push({ t.x - 1, t.y});
		q.push({ t.x, t.y + 1});
		q.push({ t.x, t.y - 1});
	}

	if (pos.size() >= 3) {
		to_change.merge(pos);
	}

	pos.clear();
}


void Game::rearrange() {
	if (abs(first_touch.first - second_touch.first) + abs(first_touch.second - second_touch.second) == 1)
		std::swap(playing_field[first_touch.first][first_touch.second], playing_field[second_touch.first][second_touch.second]);
	first_touch = std::pair<int, int>({ -1, -1 });
	second_touch = first_touch;
}



void Game::changing() {
	std::set<changing_box> pr;
	for (auto u : to_change) {
		if (existance({ u.x, u.y }) && playing_field[u.x][u.y]->get_color() != COLOR::Black) {
			pr.merge(playing_field[u.x][u.y]->activate(u.x, u.y));
			playing_field[u.x][u.y]->change_color(u.color);
		}
	}
	std::swap(to_change, pr);
}

void Game::mechanics() {

	t_time++;
	std::pair<int, int> for_comparison({ -1, -1 });

	if (to_change.empty() && is_gravity && not_black 
		&& !(first_touch != for_comparison && second_touch != for_comparison)) {
		check_connect();
		if (!to_change.empty()) t_time = 0;
		return;
	}

	if (t_time >= delay) {
		t_time = 0;
		
		if (first_touch != for_comparison && second_touch != for_comparison) {
			rearrange();
			return;
		}

		if (!to_change.empty()) {
			changing();
			is_gravity = false;
			not_black = false;
			return;
		}

		if (!is_gravity) {
			is_gravity = true;
			gravity();
			return;
		}

		if (!not_black) {
			not_black = true;
			make_new();
		}
	}

	
}