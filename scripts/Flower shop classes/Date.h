#ifndef UNTITLED_DATE_H
#define UNTITLED_DATE_H

#include <string>
#include <iostream>

class Date {
protected:
	int week_;
	int year_;

public:
	Date() : week_(0), year_(0) {};
	Date(int w, int y) : week_(w), year_(y) {};
	Date(const std::string&);
	Date(const Date &obj) : week_(obj.week_), year_(obj.year_) {};

	std::string getDateString() const;
	int getWeek() const;
	int getYear() const;

	void setDate(int, int);
	void setDate(const std::string&);
	void setWeek(int);
	void setYear(int);

	void show() const;
};
#endif // ! UNTITLED_DATE_H


