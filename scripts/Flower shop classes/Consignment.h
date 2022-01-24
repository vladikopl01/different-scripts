#ifndef UNTITLED_CONSIGNMENT_H
#define UNTITLED_CONSIGNMENT_H

#include "FlowerProduct.h"

#include <string>
#include <iostream>

class Consignment : public FlowerProduct {
protected:
	int quantity_;
	double totalPrice_;

public:
	Consignment() : quantity_(0), totalPrice_(0), FlowerProduct() {};
	Consignment(const std::string &, const std::string &, FlowerType, double, int);
	Consignment(const FlowerProduct &, int);
	Consignment(const Consignment &);

	int getQuantity() const;
	double getTotalPrice() const;

	void setQuantity(int);

	virtual void show() const override;
};

#endif // !UNTITLED_CONSIGNMENT_H



