#include<iostream>
#include<fstream>
#include"BaseClass.h"
#include"InputException.h"

BaseClass::BaseClass() {
	nonEmptyString_ = "Not an empty string";
	progressInPercent_ = 100;
	abs_ = 0;
}

BaseClass::BaseClass(std::string nonEmptyString, float progressInPercent, int abs) {
	nonEmptyString_ = nonEmptyString;
	progressInPercent_ = progressInPercent;
	abs_ = abs;
	if (nonEmptyString_.length() <= 1) {
		throw InputException("(Nearly) empty string");
	}
	if (progressInPercent_ < 0 || progressInPercent > 100) {
		throw InputException("Percentage should be in range 0-100");
	}
	if (abs <= 0) {
		throw InputException("Absolute value should be above 0");
	}
}

std::string BaseClass::getNonEmptyString() {
	return nonEmptyString_;
}

float BaseClass::getProgressInPercent() {
	return progressInPercent_;
}

int BaseClass::getAbs() {
	return abs_;
}

void BaseClass::setNonEmptyString(const std::string& nonEmptyString) {
	nonEmptyString_ = nonEmptyString;
	if (nonEmptyString_.length() <= 1) {
		throw InputException("(Nearly) empty string");
	}
}

void BaseClass::setProgressInPercent(const float& progressInPercent) {
	progressInPercent_ = progressInPercent;
	if (progressInPercent_ < 0 || progressInPercent > 100) {
		throw InputException("Percentage should be in range 0-100");
	}
}

void BaseClass::setAbs(const int& abs) {
	abs_ = abs;
	if (abs <= 0) {
		throw InputException("Absolute value should be above 0");
	}
}

void BaseClass::writeObject(std::ostream& write) {
	int str_size = nonEmptyString_.size() + 1;
	write.write(reinterpret_cast<char*>(&str_size), sizeof(int));
	char* chrs = new char[str_size];
	strcpy(chrs, nonEmptyString_.c_str());
	write.write(reinterpret_cast<char*>(&chrs[0]), sizeof(char) * str_size);
	write.write(reinterpret_cast<char*>(&progressInPercent_), sizeof(float));
	write.write(reinterpret_cast<char*>(&abs_), sizeof(int));
	delete[]chrs;
}

void BaseClass::readObject(std::istream& read) {
	int str_size = 0;
	read.read(reinterpret_cast<char*>(&str_size), sizeof(int));
	char* chrs = new char[str_size];
	read.read(reinterpret_cast<char*>(&chrs[0]), sizeof(char) * str_size);
	nonEmptyString_ = chrs;
	read.read(reinterpret_cast<char*>(&progressInPercent_), sizeof(float));
	read.read(reinterpret_cast<char*>(&abs_), sizeof(int));
	delete[]chrs;
}