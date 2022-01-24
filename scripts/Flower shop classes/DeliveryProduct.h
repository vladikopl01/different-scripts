#ifndef UNTITLED_DELIVERYPRODUCT_H
#define UNTITLED_DELIVERYPRODUCT_H

#include "Consignment.h"
#include "Date.h"

class DeliveryProduct : public Consignment, public Date {
public:
	DeliveryProduct() : Consignment(), Date() {};
	DeliveryProduct(const std::string &, const std::string &, FlowerType, double, int, int, int);
	DeliveryProduct(const Consignment &, const Date &);
	DeliveryProduct(const DeliveryProduct &);

	Consignment getConsignment() const;
	Date getDate() const;

	void setConsignment(const Consignment &);
	void setDate(const Date &);

	virtual void show() const override;
};
#endif // !UNTITLED_DELIVERYPRODUCT_H





