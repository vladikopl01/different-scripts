#ifndef LIST_OF_BASE_CLASS_
#define LIST_OF_BASE_CLASS_
#include<fstream>
#include"BaseClass.h"

class ListOfBaseClass {
	int baseClassArrayLength_;
	BaseClass* baseClassArray_;
public:
	ListOfBaseClass();
	ListOfBaseClass(BaseClass* baseClassArray, int baseClassLength);
	~ListOfBaseClass();
	int getSizeOfBazeClassArray();
	BaseClass* getBaseClassArray();
	void setBaseClassArray(BaseClass* baseClassArray, const int& length);
	void writeObject(std::ofstream& writeFile);
	void readObject(std::istream& read);
};
#endif