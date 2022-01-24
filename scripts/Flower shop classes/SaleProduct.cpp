#include "SaleProduct.h"

SaleProduct::SaleProduct(const std::string &n, const std::string &c, FlowerType t, double p, int q, int w, int y) :
	Consignment(n, c, t, p, q), Date(w, y) {}

SaleProduct::SaleProduct(const Consignment &consignment, const Date &date) :
	Consignment(consignment), Date(date) {}

SaleProduct::SaleProduct(const SaleProduct &obj) :
	Consignment(obj), Date(obj) {}

Consignment SaleProduct::getConsignment() const {
	return Consignment(*this);
}

Date SaleProduct::getDate() const {
	return Date(*this);
}

void SaleProduct::setConsignment(const Consignment &consignment) {
	(Consignment &)(*this) = consignment;
}
void SaleProduct::setDate(const Date &date) {
	(Date &)(*this) = date;
}

void SaleProduct::show() const {
	Consignment::show();
	Date::show();
}
