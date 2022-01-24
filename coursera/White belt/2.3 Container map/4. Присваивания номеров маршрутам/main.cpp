#include <iostream>
#include <vector>
#include <string>
#include <map>

int main() {
	std::map<std::vector<std::string>, int> buses;
	
	std::string stop;
	int num_of_stops;
	
	int num_of_com;
	std::cin >> num_of_com;

	for (int i = 0; i < num_of_com; i++) {
		std::cin >> num_of_stops;
		std::vector<std::string> stops(num_of_stops);

		for (std::string &stop : stops) {
			std::cin >> stop;
		}

		if (buses.count(stops)) {
			std::cout << "Already exists for " << buses[stops] << '\n';
		}
		else {
			const int route_num = buses.size() + 1;
			buses[stops] = route_num;
			std::cout << "New bus " << buses[stops] << '\n';
		}
	}

	return 0;
}