#include "Consignment.h"

Consignment::Consignment(const std::string &n, const std::string &c, FlowerType t, double p, int q) : 
	FlowerProduct(n, c, t, p) {
	this->quantity_ = q;
	this->totalPrice_ = this->price_ * this->quantity_;
}

Consignment::Consignment(const FlowerProduct &flowerProduct, int q) : 
	FlowerProduct(flowerProduct) {
	this->quantity_ = q;
	this->totalPrice_ = this->price_ * this->quantity_;
}

Consignment::Consignment(const Consignment &obj) : 
	FlowerProduct(obj) {
	this->quantity_ = obj.quantity_;
	this->totalPrice_ = obj.totalPrice_;
}

int Consignment::getQuantity() const {
	return this->quantity_;
}

double Consignment::getTotalPrice() const {
	return this->totalPrice_;
}

void Consignment::setQuantity(int q) {
	this->quantity_ = q;
	this->totalPrice_ = this->price_ * this->quantity_;
}

void Consignment::show() const {
	FlowerProduct::show();
	std::cout << "Quantity: " << this->quantity_ << '\n';
	std::cout << "Total cost: " << this->totalPrice_ << '\n';
}