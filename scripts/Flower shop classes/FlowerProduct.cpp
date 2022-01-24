#include "FlowerProduct.h"

FlowerProduct::FlowerProduct(const std::string &n, const std::string &c, FlowerType t, double p) : 
	Flower(n, c) {
	this->type_ = t;
	this->price_ = p;
}

FlowerProduct::FlowerProduct(const Flower &flower, FlowerType t, double p) : 
	Flower(flower) {
	this->type_ = t;
	this->price_ = p;
}

FlowerProduct::FlowerProduct(const FlowerProduct &obj) : 
	Flower(obj) {
	this->type_ = obj.type_;
	this->price_ = obj.price_;
}

std::string FlowerProduct::getTypeName() const {
	switch (this->type_) {
	case FlowerType::flower_pot:
		return "Flower pot";
	case FlowerType::bouquet:
		return "Bouquet";
	case FlowerType::by_the_piece:
		return "By the piece";
	default:
		return "None";
	}
}

FlowerType FlowerProduct::getType() const {
	return this->type_;
}

double FlowerProduct::getPrice() const {
	return this->price_;
}

void FlowerProduct::setType(FlowerType t) {
	this->type_ = t;
}

void FlowerProduct::setPrice(double p) {
	this->price_ = p;
}

void FlowerProduct::show() const {
	Flower::show();
	std::cout << "Type: " << this->getTypeName() << '\n';
	std::cout << "Price: " << this->price_ << '\n';
}
