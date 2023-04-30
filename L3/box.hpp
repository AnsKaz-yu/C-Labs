#include <iostream>
#include <ctime>

enum class COLOR{Red, Green, Blue, Yellow, Purple, Light_blue, Brown, Orange, Dark_grey, Black};
enum class TYPE{box, bomb, bonus};
class Box {
public:
	COLOR color;
	TYPE type;
	Box() : color{ (rand() + time(NULL)) % 9 }, screen_size(10) {
		int var = (rand() + time(NULL)) % 100;
		if (var < 3) {
			type = TYPE::bomb;
			return;
		}

		if (var < 5) {
			type = TYPE::bonus;
			return;
		}

		type = TYPE::box;
	}
	
	~Box() = default;
	
	void change_color(COLOR color) {
		this->color = color;
	}

	void change_screen_size(int screen_size) {
		this->screen_size = screen_size;
	}

	void draw(int x, int y, bool frame) const;

private:
	
	int screen_size;

	int type_analysis() const;
	void draw_n_gon(int x, int y) const;
	void set_color() const;
};