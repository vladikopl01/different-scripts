#ifndef UNTITLED_ROUTECLASS_H
#define UNTITLED_ROUTECLASS_H
#include <iostream>
#include <string>

class RouteClass {
private:
	int number_;
	std::string start_;
	std::string end_;
	int length_;
	int numOfStops_;
	int intervalH_;
	int intervalM_;
	int durationH_;
	int durationM_;

	char *name_;
public:
	//Default constructor
	explicit RouteClass();
	//Initialization constructors
	RouteClass(int, const std::string &, const std::string &, 
		int, int, int, int, int, int, const char *);
	RouteClass(int, const std::string &, const std::string &, 
		int, int, const std::string &, const std::string &, const char *);
	//Copy constructor
	RouteClass(const RouteClass &);
	//Default destructor
	~RouteClass();

	//Getters
	int getNumber() const;
	std::string getStart() const;
	std::string getEnd() const;
	int getLength() const;
	int getNumberOfStops() const;
	std::string getInterval() const;
	std::string getDuration() const;
	char *getName() const;

	//Setters
	bool setNumber(int);
	bool setStart(const std::string &);
	bool setEnd(const std::string &);
	bool setLength(int);
	bool setNumberOfStops(int);
	bool setInterval(int, int);
	bool setDuration(int, int);
	bool setName(const char *);

	//Overload setters as clases methods
	bool setInterval(const std::string &);
	bool setDuration(const std::string &);

	//Overload operators
	RouteClass &operator=(const RouteClass &);
	RouteClass operator+(const RouteClass &);
	RouteClass &operator+=(const RouteClass &);

	friend bool operator==(const RouteClass &, const RouteClass &);
	friend bool operator!=(const RouteClass &, const RouteClass &);
	friend bool operator<(const RouteClass &, const RouteClass &);
	friend bool operator>(const RouteClass &, const RouteClass &);
	friend bool operator<=(const RouteClass &, const RouteClass &);
	friend bool operator>=(const RouteClass &, const RouteClass &);

	operator std::string() const;

	//Get full object data
	std::string getData() const;

private:
	bool isValidNumber();
	bool isValidStart();
	bool isValidEnd();
	bool isValidLength();
	bool isValidNumberOfStops();
	bool isValidInterval();
	bool isValidDuration();
	bool isValidName();
	bool isValidObject();
};

#endif // !UNTITLED_ROUTECLASS_H