#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

int main() {
	std::ifstream input;
	input.open("input.txt");

	double num;

	std::cout << std::fixed << std::setprecision(3);

	if (input.is_open()) {
		while (input >> num) {
			std::cout << num << '\n';
		}
	}

	input.close();
	return 0;
}
