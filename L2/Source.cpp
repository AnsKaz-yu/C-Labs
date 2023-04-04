#include <iostream>
#include <ctime>
#include "Teacher.hpp"

int main() {
	Teacher t;
	char command;
	while (std::cin >> command && command != '0') {
		switch (command) {
		case '+': {
			std::string student_name;
			std::cin >> student_name;
			t.add_new_student(student_name, time(NULL) + rand());
			break;
		}
		case '!': {
			std::string file_name;
			std::cin >> file_name;
			t.new_test(file_name);
			break;
		}
		case '?': {
			t.show_statement();
			break;
		}
		case '=': {
			float new_accurancy;
			std::cin >> new_accurancy;
			t.set_accurancy(new_accurancy);
			break;
		}
		}
	}
}