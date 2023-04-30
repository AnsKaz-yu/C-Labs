#include <iostream>
#include <vector>
#include <set>
#include "box.hpp"

class Game {
public:
	std::set<std::pair<int, int> > to_delete;
	std::vector<std::pair<int, int> > bonus_and_bomb;
	std::pair<int, int> first_touch, second_touch;

	Game() {
		screen_size = 10;
		time = 0; delay = 700;
		playing_field.resize(screen_size, std::vector<Box>(screen_size));

		for (int x = 0; x < screen_size; x++) {
			for (int y = 0; y < screen_size; y++) {
				Box p;
				std::swap(p, playing_field[x][y]);
			}
		}
			
		first_touch = { -1, -1 };
		second_touch = { -1, -1 };

		is_gravity = true;
		not_black = true;
	}

	~Game() {
		std::vector<std::vector<Box>> pr;
		swap(pr, playing_field);
		to_delete.clear();
		bonus_and_bomb.clear();
	};

	void init_game(int argc, char** argv);
	void draw();
	void rearrange();
	void mechanics();

private:
	std::vector<std::vector<Box>> playing_field;
	int screen_size;
	int time, delay;


	void check_connect();
	void register_auxiliary_functions();
	void find_connect_comp(std::pair<int, int> t);
	void active_bonus(std::pair<int, int> t);
	void active_bomb(std::pair<int, int> t);
	bool is_gravity;
	bool not_black;
	void gravity();
	void make_new();
};