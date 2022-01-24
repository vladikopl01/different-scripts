#include "Flower.h"

std::string Flower::getName() const {
	return this->name_;
}

std::string Flower::getColor() const {
	return this->color_;
}

void Flower::setName(const std::string &n) {
	this->name_ = n;
}

void Flower::setColor(const std::string &c) {
	this->color_ = c;
}

void Flower::show() const {
	std::cout << "Name: " << this->name_ << '\n';
	std::cout << "Color: " << this->color_ << '\n';
}