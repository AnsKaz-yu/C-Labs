#pragma once

enum class COLOR { Red, Green, Blue, Yellow, Purple, Light_blue, Brown, Orange, Dark_grey, Black };
class changing_box
{
public:
	int x, y;
	COLOR color;

	friend bool operator< (const changing_box& c1, const changing_box& c2)
	{
		if (c1.x == c2.x) return (c1.y < c2.y);
		return (c1.x < c2.x);
	}

	friend bool operator> (const changing_box& c1, const changing_box& c2)
	{
		if (c1.x == c2.x) return (c1.y > c2.y);
		return (c1.x > c2.x);
	}

};




