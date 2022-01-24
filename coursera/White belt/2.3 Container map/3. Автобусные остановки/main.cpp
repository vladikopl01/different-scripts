#include <iostream>
#include <vector>
#include <string>
#include <map>

int main() {
	std::map<std::string, std::vector<std::string>> buses_to_stops, stops_to_buses;

	int num_of_commands;
	std::cin >> num_of_commands;

	for (int i = 0; i < num_of_commands; i++) {
		std::string command;
		std::cin >> command;

		if (command == "NEW_BUS") {
			std::string bus;
			std::cin >> bus;

			int stop_count;
			std::cin >> stop_count;

			std::vector<std::string> &stops = buses_to_stops[bus];
			stops.resize(stop_count);

			for (std::string &stop : stops) {
				stops_to_buses[stop].push_back(bus);
			}
		}

		if (command == "BUSES_FOR_STOP") {
			std::string stop;
			std::cin >> stop;

			if (stops_to_buses.count(stop) == 0) {
				std::cout << "No stop\n";
			}
			else {
				for (const std::string &bus : stops_to_buses[stop]) {
					std::cout << bus << " ";
				}
				std::cout << '\n';
			}
		}

		if (command == "STOPS_FOR_BUS") {
			std::string bus;
			std::cin >> bus;

			if (buses_to_stops.count(bus) == 0) {
				std::cout << "No bus\n";
			}
			else {
				for (const std::string &stop : buses_to_stops[bus]) {
					if (stops_to_buses[stop].size() == 1) {
						std::cout << "no interchange";
					}
					else {
						for (const std::string &other_bus : stops_to_buses[stop]) {
							if (bus != other_bus) {
								std::cout << other_bus << " ";
							}
						}
					}
					std::cout << '\n';
				}
			}
		}

		if (command == "ALL_BUSES") {
			if (buses_to_stops.empty()) {
				std::cout << "No buses\n";
			}
			else {
				for (const auto &bus_item : buses_to_stops) {
					std::cout << "Bus " << bus_item.first << ": ";

					for (const std::string &stop : bus_item.second) {
						std::cout << stop << " ";
					}
					std::cout << '\n';
				}
			}
		}
	}

	return 0;
}