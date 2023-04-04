#pragma once
#include <iostream>
#include "Solver.hpp"

class Student:public Solver {
public:
	std::string name;

	Student(std::string n_name, int n_reability) {
		name = n_name;
		reability = n_reability % 101;
	}

	
};