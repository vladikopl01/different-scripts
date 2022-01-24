#include "lab03.h"

RouteClass::RouteClass() {
	number_ = 0;
	start_ = "Start";
	end_ = "End";
	length_ = 1;
	numOfStops_ = 2;
	intervalH_ = 12;
	intervalM_ = 0;
	durationH_ = 12;
	durationM_ = 0;

	name_ = new char[5];
	std::strcpy(name_, "Name");

	std::cout << "Default constructor for " << this << '\n';
}

//Init constructor (time by int)
RouteClass::RouteClass(int n, const std::string &start, const std::string &end, 
	int l, int stops, int iH, int iM, int dH, int dM, const char *name) {
	number_ = n;
	if (!isValidNumber()) number_ = 0;

	start_ = start;
	if (!isValidStart()) start_ = "Start";

	end_ = end;
	if (!isValidEnd()) end_ = "End";

	length_ = l;
	if (!isValidLength()) length_ = 1;
	
	numOfStops_ = stops;
	if (!isValidNumberOfStops()) numOfStops_ = 2;
	
	intervalH_ = iH;
	intervalM_ = iM;
	if (!isValidInterval()) {
		intervalH_ = 12;
		intervalM_ = 0;
	}
	
	durationH_ = dH;
	durationM_ = dM;
	if (!isValidDuration()) {
		durationH_ = 12;
		durationM_ = 0;
	}

	if (name) {
		name_ = new char[std::strlen(name) + 1];
		std::strcpy(name_, name);
		
		if (!isValidName()) name_ = nullptr;
	}
	else {
		name_ = nullptr;
	}

	std::cout << "Initialization constructor 1 for " << this << '\n';
}

//Init constructor (time by string)
RouteClass::RouteClass(int n, const std::string &start, const std::string &end,
	int l, int stops, const std::string &interval, const std::string &duration, const char *name) {
	number_ = n;
	if (!isValidNumber()) number_ = 0;

	start_ = start;
	if (!isValidStart()) start_ = "Start";

	end_ = end;
	if (!isValidEnd()) end_ = "End";

	length_ = l;
	if (!isValidLength()) length_ = 1;

	numOfStops_ = stops;
	if (!isValidNumberOfStops()) numOfStops_ = 2;

	this->setInterval(interval);
	this->setDuration(duration);

	if (name) {
		name_ = new char[std::strlen(name) + 1];
		std::strcpy(name_, name);

		if (!isValidName()) name_ = nullptr;
	}
	else {
		name_ = nullptr;
	}

	std::cout << "Initialization constructor 2 for " << this << '\n';
}

RouteClass::RouteClass(const RouteClass &other) {
	number_ = other.number_;
	start_ = other.start_;
	end_ = other.end_;
	length_ = other.length_;
	numOfStops_ = other.numOfStops_;
	intervalH_ = other.intervalH_;
	intervalM_ = other.intervalM_;
	durationH_ = other.durationH_;
	durationM_ = other.durationM_;

	name_ = new char[std::strlen(other.name_) + 1];
	std::strcpy(name_, other.name_);

	std::cout << "Copy constructor from " << &other << " into " << this << '\n';
}

RouteClass::~RouteClass() {
	delete[]name_;
	std::cout << "Destructor for " << this << '\n';
}

//Getters
int RouteClass::getNumber() const {
	return number_;
}

std::string RouteClass::getStart() const {
	return start_;
}

std::string RouteClass::getEnd() const {
	return end_;
}

int RouteClass::getLength() const {
	return length_;
}

int RouteClass::getNumberOfStops() const {
	return numOfStops_;
}

std::string RouteClass::getInterval() const {
	std::string hours = std::to_string(intervalH_);
	std::string mins = std::to_string(intervalM_);

	if (intervalH_ < 10) {
		hours = '0' + hours;
	}

	if (intervalM_ < 10) {
		mins = '0' + mins;
	}

	return hours + ':' + mins;
}

std::string RouteClass::getDuration() const {
	std::string hours = std::to_string(durationH_);
	std::string mins = std::to_string(durationM_);

	if (durationH_ < 10) {
		hours = '0' + hours;
	}

	if (durationM_ < 10) {
		mins = '0' + mins;
	}

	return hours + ':' + mins;
}

char *RouteClass::getName() const {
	return name_;
}

//Setters
bool RouteClass::setNumber(int newNumber) {
	number_ = newNumber;
	if (!isValidNumber()) {
		number_ = 0;
		return false;
	}
	return true;
}

bool RouteClass::setStart(const std::string &newStart) {
	start_ = newStart;
	if (!isValidStart()) {
		start_ = "Start";
		return false;
	}
	return true;
}

bool RouteClass::setEnd(const std::string &newEnd) {
	end_ = newEnd;
	if (!isValidEnd()) {
		end_ = "End";
		return false;
	}
	return true;
}

bool RouteClass::setLength(int newLength) {
	length_ = newLength;
	if (!isValidLength()) {
		length_ = 1;
		return false;
	}
	return true;
}

bool RouteClass::setNumberOfStops(int newStops) {
	numOfStops_ = newStops;
	if (!isValidNumberOfStops()) {
		numOfStops_ = 2;
		return false;
	}
	return true;
}

bool RouteClass::setInterval(int newHours, int newMin) {
	intervalM_ = newMin;
	intervalH_ = newHours;

	if (!isValidInterval()) {
		intervalH_ = 12;
		intervalM_ = 0;
		return false;
	}
	return true;
}

bool RouteClass::setDuration(int newHours, int newMin) {
	durationM_ = newMin;
	durationH_ = newHours;

	if (!isValidDuration()) {
		durationM_ = 12;
		durationM_ = 0;
		return false;
	}
	return true;
}

bool RouteClass::setName(const char *newName) {
	if (newName) {
		if (name_) delete[]name_;
		name_ = new char[std::strlen(newName) + 1];
		std::strcpy(name_, newName);

		if (!isValidName()) {
			name_ = nullptr;
			return false;
		}
	}
	else {
		name_ = nullptr;
	}
	return true;
}

//Overload setters as clases methods
bool RouteClass::setInterval(const std::string &time) {
	auto iter = time.find(':');
	if (iter == std::string::npos || 
		iter == time.size() - 1) {
		std::cout << "Wrong interval_ parameter. Must be correct HH:MM!\n";
		return false;
	}

	this->intervalM_ = std::stoi(time.substr(0, iter));
	this->intervalH_ = std::stoi(time.substr(iter + 1));

	if (!isValidInterval()) {
		this->intervalH_ = 12;
		this->intervalM_ = 0;
		return false;
	}
	return true;
}

bool RouteClass::setDuration(const std::string &time) {
	auto iter = time.find(':');
	if (iter == std::string::npos ||
		iter == time.size() - 1) {
		std::cout << "Wrong duration_ parameter. Must be correct HH:MM\n";
		return false;
	}

	this->durationM_ = std::stoi(time.substr(0, iter));
	this->durationH_ = std::stoi(time.substr(iter + 1));

	if (!isValidDuration()) {
		this->durationH_ = 12;
		this->durationM_ = 0;
		return false;
	}
	return true;
}

//Operators
RouteClass &RouteClass::operator=(const RouteClass &other) {
	std::cout << "Oparator = was called to copy from " << &other << " into " << this << '\n';

	if (this == &other) {
		return *this;
	}


	if (other.name_) {
		if (this->name_) delete[]this->name_;
		this->name_ = new char[std::strlen(other.name_) + 1];
		std::strcpy(this->name_, other.name_);
	}
	else {
		this->name_ = nullptr;
	}

	this->number_ = other.number_;
	this->start_ = other.start_;
	this->end_ = other.end_;
	this->length_ = other.length_;
	this->numOfStops_ = other.numOfStops_;
	this->intervalH_ = other.intervalH_;
	this->intervalM_ = other.intervalM_;
	this->durationH_ = other.durationH_;
	this->durationM_ = other.durationM_;

	return *this;
}

RouteClass RouteClass::operator+(const RouteClass &right) {
	std::cout << "Operator + for obj+obj from " << this << " + " << &right << '\n';

	RouteClass newRoute;

	if (this->name_ && right.name_) {
		newRoute.name_ = new char[std::strlen(this->name_) + std::strlen(right.name_) + 4];
		std::strcpy(newRoute.name_, this->name_);
		std::strcat(newRoute.name_, " + ");
		std::strcat(newRoute.name_, right.name_);
	}
	else if (this->name_) {
		newRoute.name_ = new char[std::strlen(this->name_) + 1];
		std::strcpy(newRoute.name_, this->name_);
	}
	else if (right.name_) {
		newRoute.name_ = new char[std::strlen(right.name_) + 1];
		std::strcpy(newRoute.name_, right.name_);
	}

	newRoute.number_ = this->number_ + right.number_;
	newRoute.start_ = this->start_;
	newRoute.end_ = right.end_;
	newRoute.length_ = this->length_ + right.length_;
	newRoute.numOfStops_ = this->numOfStops_ + right.numOfStops_;

	newRoute.intervalM_ = this->intervalM_ + right.intervalM_;
	newRoute.intervalH_ = this->intervalH_ + right.intervalH_;
	newRoute.intervalH_ += int(newRoute.intervalM_ / 60);
	newRoute.intervalM_ %= 60;
	newRoute.intervalH_ %= 24;

	newRoute.durationM_ = this->durationM_ + right.durationM_;
	newRoute.durationH_ = this->durationH_ + right.durationH_;
	newRoute.durationH_ += int(newRoute.durationM_ / 60);
	newRoute.durationM_ %= 60;
	newRoute.durationH_ %= 24;

	return newRoute;
}

RouteClass &RouteClass::operator+=(const RouteClass &right) {
	std::cout << "Operator += to " << this << " from " << &right << '\n';


	if (this->name_ && right.name_) {
		char *temp = this->name_;
		this->name_ = new char[std::strlen(temp) + std::strlen(right.name_) + 4];
		std::strcpy(this->name_, temp);
		std::strcat(this->name_, " + ");
		std::strcat(this->name_, right.name_);
		delete temp;
	}
	else if (right.name_) {
		this->name_ = new char[std::strlen(right.name_) + 1];
		std::strcpy(this->name_, right.name_);
	}


	this->number_ += right.number_;
	this->end_ = right.end_;
	this->length_ += right.length_;
	this->numOfStops_ += right.numOfStops_;

	this->intervalM_ += right.intervalM_;
	this->intervalH_ += right.intervalH_;
	this->durationH_ += int(this->intervalM_ / 60);
	this->intervalM_ %= 60;
	this->intervalH_ %= 24;

	this->durationM_ += right.durationM_;
	this->durationH_ += right.durationH_;
	this->durationH_ += int(this->durationM_ / 60);
	this->durationM_ %= 60;
	this->durationH_ %= 24;

	return *this;
}

bool operator==(const RouteClass &left, const RouteClass &right) {
	std::cout << "Operator == for " << &left << " and " << &right << '\n';

	if (&left == &right) {
		return true;
	}

	if (left.number_ == right.number_ &&
		left.start_ == right.start_ &&
		left.end_ == right.end_ &&
		left.length_ == right.length_ &&
		left.numOfStops_ == right.numOfStops_ &&
		left.intervalH_ == right.intervalH_ &&
		left.intervalM_ == right.intervalM_ &&
		left.durationH_ == right.durationH_ &&
		left.durationM_ == right.durationM_ &&
		left.name_ && right.name_ &&
		!std::strcmp(left.name_, right.name_)) {
	}
	return false;
}

bool operator!=(const RouteClass &left, const RouteClass &right) {
	std::cout << "Operator != for " << &left << " and " << &right << '\n';
	return !(left == right);
}

bool operator<(const RouteClass &left, const RouteClass &right) {
	std::cout << "Operator < for " << &left << " and " << &right << '\n';
 
	if (left.length_ < right.length_ ||
		left.numOfStops_ < right.numOfStops_ ||
		left.getInterval() < right.getInterval() ||
		left.getDuration() < right.getDuration()) {
		return true;
	}
	return false;
}

bool operator>(const RouteClass &left, const RouteClass &right) {
	std::cout << "Operator > for " << &left << " and " << &right << '\n';
	return right < left;
}

bool operator<=(const RouteClass &left, const RouteClass &right) {
	std::cout << "Operator <= for " << &left << " and " << &right << '\n';
	return !(left > right);
}

bool operator>=(const RouteClass &left, const RouteClass &right) {
	std::cout << "Operator >= for " << &left << " and " << &right << '\n';
	return !(left < right);
}

RouteClass::operator std::string() const {
	std::cout << "Operator string() for " << this << '\n';

	return (this->name_ ? std::string(this->name_) + ' ' : "") +
		std::to_string(this->number_) + ' ' +
		this->start_ + ' ' +
		this->end_ + ' ' +
		std::to_string(this->length_) + ' ' +
		std::to_string(this->numOfStops_) + ' ' +
		this->getInterval() + ' ' +
		this->getDuration();
}

//Get full object data
std::string RouteClass::getData() const {
	return std::string(*this);
}

//Validators
bool RouteClass::isValidNumber() {
	if (number_ < 0) {
		std::cout << "Wrong number_ parameter. Must be >= 0!\n";
		return false;
	}
	return true;
}

bool RouteClass::isValidStart() {
	if (start_.size() < 1) {
		std::cout << "Wrong start_ parameter. Should not be empty!\n";
		return false;
	}
	return true;
}

bool RouteClass::isValidEnd() {
	if (end_.size() < 1) {
		std::cout << "Wrong end_ parameter. Should not be empty!\n";
		return false;
	}
	return true;
}

bool RouteClass::isValidLength() {
	if (length_ <= 0) {
		std::cout << "Wrong length_ parameter. Must be > 0!\n";
		return false;
	}
	return true;
}

bool RouteClass::isValidNumberOfStops() {
	if (numOfStops_ <= 1) {
		std::cout << "Wrong numOfStops_ parameter. Must be > 1!\n";
		return false;
	}
	return true;
}

bool RouteClass::isValidInterval() {
	if (intervalH_ < 0 || intervalH_ > 24 ||
		intervalM_ < 0 || intervalM_ > 60) {
		std::cout << "Wrong interval_ parameter. Must be correct HH:MM!\n";
		return false;
	}
	return true;
}

bool RouteClass::isValidDuration() {
	if (durationH_ < 0 || durationM_ > 24 ||
		durationM_ < 0 || durationM_ > 60) {
		std::cout << "Wrong duration_ parameter. Must be correct HH:MM!\n";
		return false;
	}
	return true;
}

bool RouteClass::isValidName() {
	if (name_ == nullptr ||
		std::strlen(name_) == 0) {
		return false;
	}
	return true;
}

bool RouteClass::isValidObject() {
	if (isValidName() && isValidNumber() &&
		isValidStart() && isValidEnd() &&
		isValidLength() && isValidNumberOfStops() &&
		isValidInterval() && isValidDuration()) {
		return true;
	}
	return false;
}
