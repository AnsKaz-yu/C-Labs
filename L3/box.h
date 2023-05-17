#include <iostream>
#include <ctime>
#include <set>
#include "changing_box.h"




class box {
public:
	box() : color{ create_rand(9) }, screen_size(10) {};

	COLOR get_color() {
		return this->color;
	}
	void change_color(COLOR color) {
		this->color = color;
	}

	virtual void draw(int x, int y, bool frame);
	virtual std::set<changing_box> activate(int x, int y);
protected:
	void draw_n_gon(int x, int y, int n) const;
	int create_rand(int t) {
		return (rand() + time(NULL)) % t;
	}
private:
	COLOR color;
	int screen_size;
	void set_color() const;
};