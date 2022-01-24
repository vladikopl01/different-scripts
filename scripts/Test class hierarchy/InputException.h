#ifndef INPUT_EXCEPTION_
#define INPUT_EXCEPTION_
#include<exception>
#include<string>

/*
 * Пользовательское исключение. Наследуется от std::exception.
 * Их может быть множество и они могут наследоваться друг от друга, как любые другие классы.
*/

class InputException : public std::exception {
    std::string exception_message_;

public:
    InputException(std::string exception_message) { exception_message_ = exception_message;}

    virtual const char* what() {return exception_message_.c_str();}
};

#endif