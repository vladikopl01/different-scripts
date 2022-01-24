#ifndef UNTITLED_FLOWERPRODUCT_H
#define UNTITLED_FLOWERPRODUCT_H

#include "Flower.h"

#include <string>
#include <iostream>

enum class FlowerType {
	flower_pot,
	bouquet,
	by_the_piece,
	none
};

class FlowerProduct : public Flower {
protected:
	FlowerType type_;
	double price_;

public:
	FlowerProduct() : type_(FlowerType::none), price_(0), Flower() {};
	FlowerProduct(const std::string &, const std::string &, FlowerType, double);
	FlowerProduct(const Flower &, FlowerType, double);
	FlowerProduct(const FlowerProduct &);

	std::string getTypeName() const;
	FlowerType getType() const;
	double getPrice() const;

	void setType(FlowerType);
	void setPrice(double);

	virtual void show() const override;
};
#endif // !UNTITLED_FLOWERPRODUCT_H