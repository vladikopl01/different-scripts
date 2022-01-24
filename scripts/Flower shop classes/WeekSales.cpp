#include "WeekSales.h"

WeekSales::vector WeekSales::getList() const {
	return this->saleList_;
}

void WeekSales::setList(const WeekSales::vector &v) {
	this->saleList_ = v;
}

void WeekSales::addSale(const SaleProduct &product) {
	this->saleList_.push_back(product);
}

SaleProduct& WeekSales::operator[](int index) {
	size_t length = this->saleList_.size();
	if (length == 0) {
		std::cout << "Week deliveries is empty!\n";
		return *(new SaleProduct());
	}
	else if (index < 0 || index >= length) {
		std::cout << "Wrong index!\n";
		return this->saleList_[length - 1];
	}
	return this->saleList_[index];
}

void WeekSales::show() const {
	for (auto &item : this->saleList_) {
		item.show();
		std::cout << '\n';
	}
}
