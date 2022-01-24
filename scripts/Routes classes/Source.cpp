#include <iostream>
#include <iomanip>
#include <vector>
#include "lab03.h"

RouteClass *createRoute();
void showRoutes(const std::vector<RouteClass*> &);

int main() {
	RouteClass t1; //Default constructor
	RouteClass t2;

	//Output object data
	std::cout << t1.getData() << '\n';

	//Operator+=
	t1 += t2;
	//Operator+ then Operator=
	t1 = t2 + t1;

	//Operator==
	if (t1 == t1) std::cout << "True\n";
	else std::cout << "False\n";
	//Operator<
	if(t1 < t2) std::cout << "True\n";
	else std::cout << "False\n";
	//Operator>
	if (t1 > t2) std::cout << "True\n";
	else std::cout << "False\n";
	//Operator<=
	if (t1 <= t2) std::cout << "True\n";
	else std::cout << "False\n";
	//Operator>=
	if (t1 >= t2) std::cout << "True\n";
	else std::cout << "False\n";

	std::string str = RouteClass(); //Implicit conversion
	str = std::string(RouteClass()); //Functional style conver.
	str = (std::string)RouteClass(); //C-style conver.

	std::cout << "\n\n";

	int choice;
	std::vector<RouteClass*> routes;

	do {
		std::cout << 
			"1 - Create route\n"
			"2 - Output all routes\n"
			"3 - Exit\n"
			"Choice: ";
		std::cin >> choice;

		switch (choice) {
		case 1:
			std::cout << "Creating route...\n";
			do {
				std::cout << "Input route data:\n";
				routes.push_back(createRoute());
				std::cout << "\nCreate another one? (1 - Yes, 0 - No): ";
				std::cin >> choice;
			} while (choice);
			break;
		case 2:
			if (routes.size()) {
				std::cout << "Showing table...\n";
				showRoutes(routes);
			}
			else {
				std::cout << "First, create some routes!\n";
			}
			break;
		case 3:
			return 0;
		}
	} while (true);
}

RouteClass *createRoute() {
	int number, length, numStops;
	std::string start, end, timeInt, timeDur, nameStr;
	int intH, intM;
	int durH, durM;

	RouteClass *newRoute = new RouteClass();

	do {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "\tName: ";
		std::cin >> nameStr;
	} while (!newRoute->setName(nameStr.c_str()));

	do {
		std::cout << "\tNumber (not less than 0): ";
		std::cin >> number;
	} while (!newRoute->setNumber(number));
	
	do {
		std::cout << "\tStart: ";
		std::cin >> start;
	} while (!newRoute->setStart(start));

	do {
		std::cout << "\tEnd: ";
		std::cin >> end;
	} while (!newRoute->setEnd(end));

	do {
		std::cout << "\tLength (more than 0): ";
		std::cin >> length;
	} while (!newRoute->setLength(length));

	do {
		std::cout << "\tNumber of stops (more than 1): ";
		std::cin >> numStops;
	} while (!newRoute->setNumberOfStops(numStops));

	do {
		std::cout << "\tInterval (HH:MM): ";
		std::cin >> timeInt;
	} while (!newRoute->setInterval(timeInt));

	do {
		std::cout << "\tDuration (HH:MM): ";
		std::cin >> timeDur;
	} while (!newRoute->setDuration(timeDur));

	return newRoute;
}

void showRoutes(const std::vector<RouteClass*> &routes) {
	std::cout << std::string(128, '=') << '\n';

	std::cout << "| " << std::setw(20) << "Name"
		<< " | " << "Number"
		<< " | " << std::setw(20) << "Route start"
		<< " | " << std::setw(20) << "Route end"
		<< " | " << "Number of stops"
		<< " | " << "Length"
		<< " | " << "Interval"
		<< " | " << "Duration" << " |\n";

	std::cout << std::string(128, '=') << '\n';

	for (const auto &item : routes) {
		std::cout << "| " << std::setw(20) << item->getName()
			<< " | " << std::setw(6) << item->getNumber()
			<< " | " << std::setw(20) << item->getStart()
			<< " | " << std::setw(20) << item->getEnd()
			<< " | " << std::setw(15) << item->getNumberOfStops()
			<< " | " << std::setw(6) << item->getLength()
			<< " | " << std::setw(8) << item->getInterval()
			<< " | " << std::setw(8) << item->getDuration() << " |\n";

		std::cout << std::string(128, '-') << '\n';
	}
}