#include "game.hpp"
#include <queue>
#define x first
#define y second

void Game::check_connect() {
	for (int x = 0; x < screen_size; x++) {
		for (int y = 0; y < screen_size; y++) {
			if (to_delete.find({ x, y }) == to_delete.end())
				find_connect_comp({ x, y });
		}
	}
}

void Game::make_new() {
	for (int x = 0; x < screen_size; x++) {
		for (int y = 0; y < screen_size; y++) {
			if (playing_field[x][y].color == COLOR::Black) {
				Box p;
				std::swap(p, playing_field[x][y]);
			}
		}
	}
}

void Game::gravity() {
	for (int x = 0; x < screen_size; x++) {
		for (int y = screen_size - 2; y >= 0; y--) {
			if (playing_field[x][y].color != COLOR::Black) {
				int yt = y;

				while (yt + 1 < screen_size && playing_field[x][yt + 1].color == COLOR::Black) {
					std::swap(playing_field[x][yt], playing_field[x][yt + 1]);
					yt++;
				}
			}
			
		}
	}
}

void Game::find_connect_comp(std::pair<int, int> t) {
	std::set<std::pair<int, int>> pos;
	std::queue<std::pair<int, int>> q;
	COLOR c = playing_field[t.first][t.second].color;
	q.push(t);
	while (!q.empty()) {
		t = q.front();
		q.pop();

		if (t.x < 0 || t.y < 0 || t.x >= screen_size || t.y >= screen_size) continue;
		if (playing_field[t.first][t.second].color != c) continue;

		int s = pos.size();
		pos.insert(t);
		if (s == pos.size()) continue;

		q.push({ t.x + 1, t.y });
		q.push({ t.x - 1, t.y });
		q.push({ t.x, t.y + 1 });
		q.push({ t.x, t.y - 1 });
	}

	if (pos.size() >= 3) {
		to_delete.merge(pos); //??????????????????
	}

	pos.clear();
}

void Game::active_bonus(std::pair<int, int> t) {
	int m[2] = { -1, 1 };
	int count = 0;
	for (auto u : m) {
		for (auto v : m) {
			if (t.x + u >= 0 && t.x + u < screen_size
				&& t.y + v >= 0 && t.y + v < screen_size
				&& playing_field[t.x + u][t.y + v].color != COLOR::Black && count < 2) {
				count++;
				playing_field[t.x + u][t.y + v].change_color(playing_field[t.x][t.y].color);
			}
		}
	}
		
}

void Game::active_bomb(std::pair<int, int> t) {
	int radius = rand() % 3 + 1;
	for (int r = 1; r <= radius; r++) {
		for (int u = 0; u <= r; u++) {
			int v = r - u;
			int m[2] = { -1, 1 };
			for (auto i: m)
				for (auto j : m) {
					if (t.x + i*u >= 0 && t.x + i*u < screen_size
						&& t.y + j*v >= 0 && t.y + j*v < screen_size
						&& playing_field[t.x + i*u][t.y + j*v].color != COLOR::Black) {
						to_delete.insert({ t.x + i*u, t.y + j*v });
					}
				}
			
			
		}
	}
}


void Game::rearrange() {
	if (abs(first_touch.first - second_touch.first) + abs(first_touch.second - second_touch.second) == 1)
		std::swap(playing_field[first_touch.first][first_touch.second], playing_field[second_touch.first][second_touch.second]);
	first_touch = std::pair<int, int>({ -1, -1 });
	second_touch = first_touch;
}

void Game::mechanics() {

	time++;
	std::pair<int, int> for_comparison({ -1, -1 });
	//std::cout<<time<<"\n\n\n";
	if (to_delete.empty() && bonus_and_bomb.empty() && is_gravity && not_black 
		&& !(first_touch != for_comparison && second_touch != for_comparison)) {
		check_connect();
		if (!to_delete.empty()) time = 0;
		return;
	}

	if (time >= delay) {
		time = 0;
		
		if (first_touch != for_comparison && second_touch != for_comparison) {
			rearrange();
			return;
		}

		if (!to_delete.empty()) {
			for (auto t : to_delete) {
				if (playing_field[t.x][t.y].type != TYPE::box) {
					bonus_and_bomb.push_back(t);
					continue;
				}
				else {
					playing_field[t.x][t.y].change_color(COLOR::Black);
				}
				
			}
			to_delete.clear();
			is_gravity = false;
			not_black = false;
			return;
		}

		if (!bonus_and_bomb.empty()) {
			while (!bonus_and_bomb.empty()) {
				std::pair<int, int> t = bonus_and_bomb.back();
				bonus_and_bomb.pop_back();
				if (playing_field[t.x][t.y].type == TYPE::bonus) {
					active_bonus(t);
				}
				else {
					active_bomb(t);
				}

				playing_field[t.x][t.y].change_color(COLOR::Black);
			}
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