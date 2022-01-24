#ifndef UNTITLED_SALEPRODUCT_H
#define UNTITLED_SALEPRODUCT_H

#include "Consignment.h"
#include "Date.h"

class SaleProduct : public Consignment, public Date {
public:
	SaleProduct() : Consignment(), Date() {};
	SaleProduct(const std::string &, const std::string &, FlowerType, double, int, int, int);
	SaleProduct(const Consignment &, const Date &);
	SaleProduct(const SaleProduct &);

	Consignment getConsignment() const;
	Date getDate() const;

	void setConsignment(const Consignment &);
	void setDate(const Date &);

	virtual void show() const override;
};
#endif // !UNTITLED_SALEPRODUCT_H



