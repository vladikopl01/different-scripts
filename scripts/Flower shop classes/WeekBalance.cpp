#include "WeekBalance.h"

WeekBalance::WeekBalance(const WeekBalance::vectorDeliveries &deliveries, const WeekBalance::vectorSales &sales) :
	WeekDeliveries(deliveries), WeekSales(sales) {
	this->countExpenses();
	this->countIncome();
	this->countProfit();
}

WeekBalance::WeekBalance(const WeekDeliveries &deliveries, const WeekSales &sales) : 
	WeekDeliveries(deliveries), WeekSales(sales) {
	this->countExpenses();
	this->countIncome();
	this->countProfit();
}

WeekBalance::WeekBalance(const WeekBalance &obj) : 
	WeekDeliveries(obj), WeekSales(obj) {
	this->countExpenses();
	this->countIncome();
	this->countProfit();
}

WeekDeliveries WeekBalance::getWeekDeliveries() const {
	return WeekDeliveries(*this);
}

WeekSales WeekBalance::getWeekSales() const {
	return WeekSales(*this);
}

double WeekBalance::getTotalExpenses() const {
	return this->totalExpenses_;
}

double WeekBalance::getTotalIncome() const {
	return this->totalIncome_;
}

double WeekBalance::getTotalProfit() const {
	return this->totalProfit_;
}

void WeekBalance::setWeekDeliveries(const WeekDeliveries & deliveries) {
	(WeekDeliveries &)(*this) = deliveries;
	this->countExpenses();
	this->countProfit();
}

void WeekBalance::setWeekSales(const WeekSales &sales) {
	(WeekSales &)(*this) = sales;
	this->countIncome();
	this->countProfit();
}

void WeekBalance::show() const {
	std::cout << "Week deliveries:\n";
	WeekDeliveries::show();
	std::cout << "Week sales:\n";
	WeekSales::show();
}

void WeekBalance::countExpenses() {
	for (auto &item : this->deliveryList_) {
		this->totalExpenses_ += item.getTotalPrice();
	}
}

void WeekBalance::countIncome() {
	for (auto &item : this->saleList_) {
		this->totalIncome_ += item.getTotalPrice();
	}
}
void WeekBalance::countProfit() {
	this->totalProfit_ = this->totalIncome_- this->totalExpenses_;
}
