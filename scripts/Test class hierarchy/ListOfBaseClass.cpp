#include<fstream>
#include"ListOfBaseClass.h"


ListOfBaseClass::ListOfBaseClass() {
	baseClassArrayLength_ = 0;
	baseClassArray_ = NULL;
}

ListOfBaseClass::ListOfBaseClass(BaseClass* baseClassArray, int baseClassLength) {
	baseClassArray_ = baseClassArray;
	baseClassArrayLength_ = baseClassLength;
}

ListOfBaseClass::~ListOfBaseClass() {
	if (baseClassArray_) {
		delete[]baseClassArray_;
	}
}

BaseClass* ListOfBaseClass::getBaseClassArray() {
	return baseClassArray_;
}

int ListOfBaseClass::getSizeOfBazeClassArray() {
	return baseClassArrayLength_;
}

void ListOfBaseClass::setBaseClassArray(BaseClass* baseClassArray, const int& length) {
	if (baseClassArray_) {
		delete[]baseClassArray_;
	}
	baseClassArray_ = baseClassArray;
	baseClassArrayLength_ = length;
}

void ListOfBaseClass::writeObject(std::ofstream& write) {
	write.write(reinterpret_cast<char*>(&baseClassArrayLength_), sizeof(int));
	for (int i = 0; i < baseClassArrayLength_; i++) {
		baseClassArray_[i].writeObject(write);
	}
}

void ListOfBaseClass::readObject(std::istream& read) {
	read.read(reinterpret_cast<char*>(&baseClassArrayLength_), sizeof(int));
	if (baseClassArray_) {
		delete[]baseClassArray_;
	}
	baseClassArray_ = new BaseClass[baseClassArrayLength_];
	for (int i = 0; i < baseClassArrayLength_; i++) {
		baseClassArray_[i].readObject(read);
	}
}