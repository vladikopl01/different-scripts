#include "DeliveryProduct.h"

DeliveryProduct::DeliveryProduct(const std::string &n, const std::string &c, FlowerType t, double p, int q, int w, int y) : 
	Consignment(n, c, t, p, q), Date(w, y) {}

DeliveryProduct::DeliveryProduct(const Consignment &consignment, const Date &date) : 
	Consignment(consignment), Date (date) {}

DeliveryProduct::DeliveryProduct(const DeliveryProduct &obj) : 
	Consignment(obj), Date(obj) {}

Consignment DeliveryProduct::getConsignment() const {
	return Consignment(*this);
}

Date DeliveryProduct::getDate() const {
	return Date(*this);
}

void DeliveryProduct::setConsignment(const Consignment &consignment) {
	(Consignment&)(*this) = consignment;
}
void DeliveryProduct::setDate(const Date &date) {
	(Date &)(*this) = date;
}

void DeliveryProduct::show() const {
	Consignment::show();
	Date::show();
}
