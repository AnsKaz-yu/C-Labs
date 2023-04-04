#pragma once
#include <iostream>
#include <ctime>

struct coefficients {
	float a, b, c;
};

class Solver {
public:
	Solver() {
		reability = 100;
	}

	std::pair<float, float> solve(coefficients C) {
		float D = Discreminant(C);

		std::pair<float, float> roots;
		if (D < 0) {
			roots = { INT_MAX, INT_MAX };
		}
		else {
			roots = CountingRoots(C, D);
		}

		//с определенной вероятностью выдаем правильный ответ
		if (CheckReability()) {
			return roots;
		}
		else {
			return { 0, 0 };
		}
			
	}

protected:
	int reability = 0;

private:
	std::pair<float, float> CountingRoots(const coefficients equation, const float D) {
		std::pair<float, float> roots;
		roots.first = (-1 * equation.b - sqrt(D)) / (2 * equation.a);
		roots.second = (-1 * equation.b + sqrt(D)) / (2 * equation.a);

		return roots;
	}


	float Discreminant(const coefficients equation) {
		float D = equation.b * equation.b - 4 * equation.a * equation.c;
		return D;
	}

	bool CheckReability() {
		int rnd = (time(NULL) + rand()) % 100 + 1;
		if (rnd <= reability) {
			return true;
		}
		else {
			return false;
		}
	}
};