#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

int main() {
	std::ifstream input;
	input.open("input.txt");

	std::string cell;

	int row, col;


	if (input.is_open()) {
		input >> row >> col;
		input.ignore(1);

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col - 1; j++) {
				std::getline(input, cell, ',');
				std::cout << std::setw(10) << cell << ' ';
			}
			std::getline(input, cell);
			std::cout << std::setw(10) << cell << '\n';
		}

		/*for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				int x;
				input >> x;
				input.ignore(1);

				std::cout << std::setw(10) << x;

				if (j != col - 1) {
					std::cout << ' ';
				}
			}

			if (i != row - 1) {
				std::cout << '\n';
			}
		}*/
	}

	input.close();
	return 0;
}
