#include "WeekDeliveries.h"

WeekDeliveries::vector WeekDeliveries::getList() const {
	return this->deliveryList_;
}

void WeekDeliveries::setList(const WeekDeliveries::vector &v) {
	this->deliveryList_ = v;
}

void WeekDeliveries::addDelivery(const DeliveryProduct &product) {
	this->deliveryList_.push_back(product);
}

DeliveryProduct& WeekDeliveries::operator[](int index) {
	size_t length = this->deliveryList_.size();
	if (length == 0) {
		std::cout << "Week deliveries is empty!\n";
		return *(new DeliveryProduct());
	}
	else if (index < 0 || index >= length) {
		std::cout << "Wrong index!\n";
		return this->deliveryList_[length - 1];
	}
	return this->deliveryList_[index];
}

void WeekDeliveries::show() const {
	for (auto &item : this->deliveryList_) {
		item.show();
		std::cout << '\n';
	}
}