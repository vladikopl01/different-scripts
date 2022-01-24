#ifndef BASE_CLASS_
#define BASE_CLASS_
#include<string>

/*
 * Самый обычный класс с геттерами и сеттерами.
 * Выделяются только методы для чтения и записи объекта в бинарный файл.
 * Можно сделать специальный "читающий" конструктор, который будет принимать стрим и создавать новый объект.
 * Можно перегрузить операторы << и >> в дружественных функциях (но это больше подходит для не-бинарных файлов).
 * Можно придумать что-то ещё.
*/

class BaseClass {
	std::string nonEmptyString_;
	float progressInPercent_;
	int abs_;

public:
	BaseClass();
	BaseClass(std::string nonEmptyString, float progressInPercent, int abs);
	std::string getNonEmptyString();
	float getProgressInPercent();
	int getAbs();
	void setNonEmptyString(const std::string& nonEmptyString);
	void setProgressInPercent(const float& progressInPercent);
	void setAbs(const int& abs);
	void writeObject(std::ostream& write);
	void readObject(std::istream& read);
};
#endif