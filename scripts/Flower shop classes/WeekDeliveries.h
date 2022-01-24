#ifndef UNTITLED_WEEKDELIVERIES_H
#define UNTITLED_WEEKDELIVERIES_H

#include <vector>
#include <iostream>

#include "DeliveryProduct.h"

class WeekDeliveries {
	using vector = std::vector<DeliveryProduct>;

protected:
	vector deliveryList_;

public:
	WeekDeliveries() = default;
	WeekDeliveries(const vector &l) : deliveryList_(l) {};
	WeekDeliveries(const WeekDeliveries &obj) : deliveryList_(obj.deliveryList_) {};

	vector getList() const;

	void setList(const vector&);

	void addDelivery(const DeliveryProduct &);

	DeliveryProduct& operator[](int);

	virtual void show() const;
};

#endif // !UNTITLED_WEEKDELIVERIES_H



