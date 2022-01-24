#include <iostream>

#include "WeekBalance.h"

int main() {
	// By default constructor
	WeekBalance myBalance1;
	std::cout << "Default balance:\n";
	std::cout << "Icnome: " << myBalance1.getTotalIncome() << "\n";
	std::cout << "Expense: " << myBalance1.getTotalExpenses() << "\n";
	std::cout << "Profit: " << myBalance1.getTotalProfit() << "\n\n";

	// By init constructor
	std::vector<DeliveryProduct> deliveries { 
		{"Tulip",	"Purple",	FlowerType::by_the_piece,	25.0,	150,	14, 2020},
		{"Rose",	"Red",		FlowerType::bouquet,		500.0,	45,		22, 2020},
		{"Lily",	"White",	FlowerType::by_the_piece,	75.0,	95,		18, 2020},
		{"Orchid",	"Orange",	FlowerType::flower_pot,		100.0,	125,	1,	2020}
	};
	std::vector<SaleProduct> sales {
		{"Lily",	"White",	FlowerType::by_the_piece,	85.0,	70,		25, 2020},
		{"Tulip",	"Purple",	FlowerType::by_the_piece,	50.0,	25,		18, 2020},
		{"Orchid",	"Orange",	FlowerType::flower_pot,		300.0,	95,		12,	2020},
		{"Rose",	"Red",		FlowerType::bouquet,		750.0,	45,		35, 2020}
	};

	WeekBalance myBalance2(deliveries, sales);
	std::cout << "Initialization balance:\n";
	std::cout << "Income: " << myBalance2.getTotalIncome() << "\n";
	std::cout << "Expense: " << myBalance2.getTotalExpenses() << "\n";
	std::cout << "Profit: " << myBalance2.getTotalProfit() << "\n\n";

	// By copy constructor
	WeekBalance myBalance3(myBalance2);
	std::cout << "Copy balance:\n";
	std::cout << "Income: " << myBalance3.getTotalIncome() << "\n";
	std::cout << "Expense: " << myBalance3.getTotalExpenses() << "\n";
	std::cout << "Profit: " << myBalance3.getTotalProfit() << "\n\n";

	Date date = myBalance2.getWeekDeliveries()[0].getDate();
	std::cout << "Date: " << date.getDateString() << "\n";
	std::cout << "Week: " << date.getWeek() << "\n";
	std::cout << "Year: " << date.getYear() << "\n\n";

	// Early(static) binding
	DeliveryProduct delivery = { "Tulip", "Purple", FlowerType::by_the_piece, 25.0, 150, 14, 2020 };
	Date *rDate = &delivery;
	
	std::cout << "Early binding:\n";
	rDate->show();
	std::cout << '\n';

	// Late(dynamic) binding
	Consignment *rCons = &delivery;

	std::cout << "Late binding:\n";
	rCons->show();
	std::cout << '\n';

	return 0;
}