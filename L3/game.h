#include <iostream>
#include <vector>
#include <set>
#include "bonus.h"

class Game {
public:
	std::set<changing_box> to_change;
	std::pair<int, int> first_touch, second_touch;

	Game() {
		screen_size = 10;
		t_time = 0; delay = 700;
		playing_field.resize(screen_size, std::vector<box*>(screen_size));

		for (int x = 0; x < screen_size; x++) {
			for (int y = 0; y < screen_size; y++) {
				box* p = create_new_box();
				std::swap(p, playing_field[x][y]);
			}
		}
			
		first_touch = { -1, -1 };
		second_touch = { -1, -1 };

		is_gravity = true;
		not_black = true;
	}

	~Game() {
		for (int x = 0; x < screen_size; x++) {
			for (int y = 0; y < screen_size; y++) {
				delete playing_field[x][y];
			}
		}
		to_change.clear();
	};

	void init_game(int argc, char** argv);
	void draw();
	void rearrange();
	void mechanics();

private:
	std::vector<std::vector<box*>> playing_field;
	int screen_size;
	int t_time, delay;

	box* create_new_box();
	void changing();
	bool existance(std::pair<int, int> u);
	void check_connect();
	void register_auxiliary_functions();
	void find_connect_comp(changing_box t);
	bool is_gravity;
	bool not_black;
	void gravity();
	void make_new();
};