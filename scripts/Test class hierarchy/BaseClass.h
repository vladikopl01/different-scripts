#ifndef BASE_CLASS_
#define BASE_CLASS_
#include<string>

/*
 * ����� ������� ����� � ��������� � ���������.
 * ���������� ������ ������ ��� ������ � ������ ������� � �������� ����.
 * ����� ������� ����������� "��������" �����������, ������� ����� ��������� ����� � ��������� ����� ������.
 * ����� ����������� ��������� << � >> � ������������� �������� (�� ��� ������ �������� ��� ��-�������� ������).
 * ����� ��������� ���-�� ���.
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