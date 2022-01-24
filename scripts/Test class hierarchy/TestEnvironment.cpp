#include <iostream>
#include <fstream>
#include"BaseClass.h"
#include"InputException.h"
#include"ListOfBaseClass.h"

BaseClass possibleInputExceptionFunction();
BaseClass possibleInputExceptionFunctionTwo();

int main()
{
    /*
    * Класс-исключение определён в InputException.h. Вам, разумеется, надо придумать своё (или свои).
    * Можно кидать исключения при вводе, из функции (или функций), которые вызываются из main.
    * Можно кидать их в методах класса, а обработку try catch делать из функций, которые вызывают методы.
    * И то, и другое одновременно скорее всего избыточно.
    * Наверное лучше просто взять первый вариант и кидать их во внешней программе при вводе,
    * убрав все throw из классов. Но тут на ваше усмотрение.
    */

    // Кидает эксепшены при вводе во внешней программе:
    possibleInputExceptionFunction();

    /* Эксепшены так же кидаются в классе, можно заключать вызов методов в блок try, 
    при поступлении неправильных параметров в методах класса будет кинут эксепшены:*/
    possibleInputExceptionFunctionTwo();

    // Сериализация-десериализация объектов с динамичными массивами в бинарных файлах:
    
    // Объекты для массива:
    BaseClass a;
    BaseClass b("111", 10.0, 10);
    BaseClass c("Original String", 3.0, 4);
    BaseClass d("Unoriginal String", 4.0, 5);

    // Массив:
    BaseClass* arr = new BaseClass[]{ a, b, c, d };

    // Класс со списком:
    ListOfBaseClass listObj(arr, 4);

    // Запись класса со списком в бинарный файл:
    std::ofstream write("binary.dat", std::ios::out | std::ios::binary);
    if (!write) {
        std::cout << "Error opening file";
        return 1;
    }
    listObj.writeObject(write);
    write.close();
    if (!write.good()) {
        std::cout << "Error writing file";
        return 1;
    }

    // Чтение в другой объект:
    std::ifstream read("binary.dat", std::ios::out | std::ios::binary);
    if (!read) {
        std::cout << "Error opening file";
        return 1;
    }
    ListOfBaseClass listObjTwo;
    listObjTwo.readObject(read);
    read.close();
    if (!read.good()) {
        std::cout << "Error reading file";
        return 1;
    }

    //Сравниваем, правильно ли записались/считались объекты:
    for (int i = 0; i < listObj.getSizeOfBazeClassArray(); i++) {
        std::cout << listObj.getBaseClassArray()[i].getNonEmptyString() << " "
            << listObj.getBaseClassArray()[i].getProgressInPercent() << " "
            << listObj.getBaseClassArray()[i].getAbs() << std::endl;
        std::cout << listObjTwo.getBaseClassArray()[i].getNonEmptyString() << " "
            << listObjTwo.getBaseClassArray()[i].getProgressInPercent() << " "
            << listObjTwo.getBaseClassArray()[i].getAbs() << std::endl << std::endl;
    }

    return 0;
}

BaseClass possibleInputExceptionFunction() {
    BaseClass base;
    std::string str = "";
    float percentage = 0;
    int abs = 0;
    try {
        std::cout << "Input string with at least 2 chars:";
        std::cin >> str;
        if (str.length() <= 1) {
            throw InputException("(Nearly) empty string was entered");
        }
        std::cout << "Input val in percent:";
        std::cin >> percentage;
        if (percentage < 0 || percentage > 100) {
            throw InputException("Percentage should be in range 0-100");
        }
        std::cout << "Input absolute value:";
        std::cin >> abs;
        if (abs < 0) {
            throw InputException("Absolute value should be above 0");
        }
    }
    catch (InputException& e) {
        std::cout << e.what();
        /* Можно рекурсивно вызвать функцию при возникновении исключительной ситуации.
        * Или дать какие-то подходящие параметры возвращаемому объекту.
        * Или придумать что-то ещё.
        */
        return possibleInputExceptionFunction();
    }
    /* При необходимости обрабатываете другие эксепшены 
    * TODO: catch other exceptions
    * ...
    * catch (exception e){...}
    */
    return base;
}

BaseClass possibleInputExceptionFunctionTwo() {
    BaseClass base;
    std::string str = "";
    std::cout << "Input string with at least 2 chars:";
    std::cin >> str;

    float percentage = 0;
    std::cout << "Input val in percent:";
    std::cin >> percentage;

    int abs = 0;
    std::cout << "Input absolute value:";
    std::cin >> abs;

    try {
        //throw определены внутри методов класса
        base.setNonEmptyString(str);
        base.setProgressInPercent(percentage);
        base.setAbs(abs);
    }
    catch (InputException& e) {
        std::cout << e.what();
        /* Можно рекурсивно вызвать функцию при возникновении исключительной ситуации.
        * Или дать какие-то подходящие параметры возвращаемому объекту
        * Или придумать что-то ещё
        */
        return possibleInputExceptionFunctionTwo();
    }
    /* При необходимости обрабатываете другие эксепшены
    * TODO: catch other exceptions
    * ...
    * catch (exception e){...}
    */
    return base;
}