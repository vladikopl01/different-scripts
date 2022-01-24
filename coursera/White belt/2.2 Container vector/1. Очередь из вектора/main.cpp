#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
	std::vector<bool> v;

	int num_commands;
	std::cin >> num_commands;

	for (int i = 0; i < num_commands; i++) {
		std::string command;
		std::cin >> command;

		if (command == "WORRY_COUNT") {
			std::cout << count(v.begin(), v.end(), true);
		}
		else {
			int n;
			std::cin >> n;

			if (command == "COME") {
				v.resize(v.size() + n, false);
			}

			if (command == "WORRY" || command == "QUIET") {
				v[n] = (command == "WORRY");
			}
		}
	}
}