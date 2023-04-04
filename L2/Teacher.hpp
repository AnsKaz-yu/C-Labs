#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
#include "Solver.hpp"
#include "Student.hpp"

class Teacher :Solver {
public:

	~Teacher() {
		test.clear();
		students.clear();
		statement.clear();
	}

	void set_accurancy(int acc) {
		varification_accurancy = acc;
	}

	

	void new_test(std::string file_name) {
		if (!(read_test(file_name))) return;
		for (const auto& u : test) {
			std::pair<float, float> tescher_solution = solve(u);
			for (const auto& p : students) {
				if (validation(tescher_solution, p->solve(u))) {
					statement[p->name]++;
				}
			}
			max_mark++;
		}
	}

	void show_statement() {
		for (const auto& u : students) {
			std::cout << u->name << ' ' << statement[u->name] << '/' << max_mark << std::endl;
		}
	}

	void add_new_student(std::string name, int reability) {
		Student* new_student = new Student(name, reability);
		students.push_back(new_student);
	}

private:
	std::vector<coefficients> test;
	std::vector<Student*> students;
	std::map<std::string, int> statement;
	int max_mark = 0;
	float varification_accurancy = 0.1;

	bool validation(std::pair<float, float> a, std::pair<float, float> b) {
		if (abs(a.first - b.first) + abs(a.second - b.second) <= varification_accurancy) {
			return true;
		}
		else {
			return false;
		}
	}

	bool read_test(std::string file_name) {
		test.clear();
		std::ifstream cinf;
		cinf.open(file_name);

		if (!(cinf.is_open())) {
			return false;
		}

		float A, B, C;
		while (cinf >> A && cinf >> B && cinf >> C) {
			test.push_back({ A, B, C });
		}

		cinf.close();

		return true;
	}

};