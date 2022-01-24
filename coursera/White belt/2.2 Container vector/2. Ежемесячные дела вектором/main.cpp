#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
	std::vector<int> days_in_months = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	int month = 0;
	std::vector<std::vector<std::string>> task_for_day(days_in_months[month]);

	int num_commands;
	std::cin >> num_commands;

	for (int i = 0; i < num_commands; i++) {
		std::string command;
		std::cin >> command;

		if (command == "NEXT") {
			month = (month + 1) % days_in_months.size();

			const int old_month = task_for_day.size();
			const int new_month = days_in_months[month];

			if (old_month > new_month) {
				for (int i = new_month; i < old_month; i++) {
					task_for_day[new_month - 1].insert(task_for_day[new_month - 1].end(), task_for_day[i].begin(), task_for_day[i].end());
				}
			}

			task_for_day.resize(new_month);
		}

		int day;
		if (command == "DUMP") {
			std::cin >> day;

			std::cout << task_for_day[day - 1].size();
			for (auto task : task_for_day[day - 1]) {
				std::cout << " " << task;
			}
			std::cout << '\n';
		}

		if (command == "ADD") {
			std::string task;
			std::cin >> day >> task;
			task_for_day[day - 1].push_back(task);
		}
	}
}