#include "Date.h"

Date::Date(const std::string &date) {
	this->setDate(date);
}

std::string Date::getDateString() const {
	return std::to_string(this->week_) + "/" + std::to_string(this->year_);
}

int Date::getWeek() const {
	return this->week_;
}

int Date::getYear() const {
	return this->year_;
}

void Date::setDate(int w, int y) {
	this->week_ = w;
	this->year_ = y;
}

void Date::setDate(const std::string &date) {
	this->week_ = std::stoi(date.substr(0, date.find('/')));
	this->year_ = std::stoi(date.substr(date.find('/') + 1));
}

void Date::setWeek(int w) {
	this->week_ = w;
}

void Date::setYear(int y) {
	this->year_ = y;
}

void Date::show() const {
	std::cout << "Week: " << this->week_ << '\n';
	std::cout << "Year: " << this->year_ << '\n';
}
