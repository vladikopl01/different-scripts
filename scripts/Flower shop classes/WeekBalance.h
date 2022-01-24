#ifndef UNTITLED_WEEKDALANCE_H
#define UNTITLED_WEEKBALANCE_H

#include "WeekDeliveries.h"
#include "WeekSales.h"

#include <vector>

class WeekBalance : public WeekDeliveries, public WeekSales {
	using vectorDeliveries = std::vector<DeliveryProduct>;
	using vectorSales = std::vector<SaleProduct>;

private:
	double totalExpenses_;
	double totalIncome_;
	double totalProfit_;

public:
	WeekBalance() : WeekDeliveries(), WeekSales(), totalExpenses_(0), totalIncome_(0), totalProfit_(0) {};
	WeekBalance(const vectorDeliveries &, const vectorSales &);
	WeekBalance(const WeekDeliveries &, const WeekSales &);
	WeekBalance(const WeekBalance &);

	WeekDeliveries getWeekDeliveries() const;
	WeekSales getWeekSales() const;
	double getTotalExpenses() const;
	double getTotalIncome() const;
	double getTotalProfit() const;

	void setWeekDeliveries(const WeekDeliveries &);
	void setWeekSales(const WeekSales &);

	virtual void show() const override;

private:
	void countExpenses();
	void countIncome();
	void countProfit();
};
#endif // !UNTITLED_WEEKDALANCE_H



