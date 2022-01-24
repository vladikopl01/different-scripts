#include <iostream>
#include <fstream>
#include <string>

int main() {
	std::ifstream input;
	input.open("input.txt");

	std::ofstream output;
	output.open("output.txt");

	std::string line;

	if (input.is_open()) {
		while (std::getline(input, line)) {
			std::cout << line << '\n';
		}
	}
	input.close();

	input.open("input.txt");
	if (output.is_open()) {
		while (std::getline(input, line)) {
			output << line << '\n';
		}
	}

	return 0;
}
