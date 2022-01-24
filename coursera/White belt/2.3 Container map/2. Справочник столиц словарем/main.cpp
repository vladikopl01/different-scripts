#include <iostream>
#include <vector>
#include <string>
#include <map>

int main() {
	std::map<std::string, std::string> capitals;

	int num;
	std::cin >> num;

	for (int i = 0; i < num; i++) {
		std::string command;
		std::cin >> command;

		std::string country;

		if (command == "CHANGE_CAPITAL") {
			std::cin >> country;
			std::string new_capital;
			std::cin >> new_capital;

			if (capitals.count(country) == 0) {
				capitals[country] = new_capital;
				std::cout << "Introduce new country " << country <<
					" with capital " << new_capital << "\n";
			}
			else if (capitals.find(country)->second == new_capital) {
				std::cout << "Country " << country 
					<< " hasn't changed its capital\n";
			}
			else {
				std::cout << "Country " << country << " has changed its capital from " <<
					capitals[country] << " to " << new_capital << "\n";
				capitals[country] = new_capital;
			}

		}

		if (command == "RENAME") {
			std::cin >> country;
			std::string new_country_name;
			std::cin >> new_country_name;

			if (country == new_country_name ||
				capitals.count(country) == 0 ||
				capitals.count(new_country_name) == 1) {
				std::cout << "Incorrect rename, skip\n";
			}
			else {
				capitals[new_country_name] = capitals[country];
				capitals.erase(country);
				std::cout << "Country " << country << " with capital "
					<< capitals[new_country_name] << " has been renamed to " <<
					new_country_name << "\n";
			}
		}

		if (command == "ABOUT") {
			std::cin >> country;
			if (capitals.count(country) == 1) {
				std::cout << "Country " << country << " has capital " 
					<< capitals[country] << '\n';
			}
			else {
				std::cout << "Country " << country << " doesn't exist\n";
			}
		}

		if (command == "DUMP") {
			if (!capitals.empty()) {
				for (auto &pair: capitals) {
					std::cout << pair.first << "/" << pair.second << " ";
				}
				std::cout << '\n';
			}
			else {
				std::cout << "There are no countries in the world\n";
			}
		}
	}

	return 0;
}