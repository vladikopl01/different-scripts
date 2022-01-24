#ifndef UNTITLED_WEEKSALES_H
#define UNTITLED_WEEKSAKES_H

#include <vector>
#include <iostream>

#include "SaleProduct.h"

class WeekSales {
	using vector = std::vector<SaleProduct>;

protected:
	vector saleList_;

public:
	WeekSales() = default;
	WeekSales(const vector & l) : saleList_(l) {};
	WeekSales(const WeekSales & obj) : saleList_(obj.saleList_) {};

	vector getList() const;

	void setList(const vector &);

	void addSale(const SaleProduct &);

	SaleProduct& operator[](int);

	virtual void show() const;
};
#endif // !UNTITLED_WEEKSALES_H



