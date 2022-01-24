#ifndef UNTITLED_FLOWER_H
#define UNTITLED_FLOWER_H

#include <string>
#include <iostream>

class Flower {
protected:
	std::string name_;
	std::string color_;

public:
	Flower() : name_(""), color_("") {};
	Flower(const std::string &n, const std::string &c) : name_(n), color_(c) {};
	Flower(const Flower &obj) : name_(obj.color_), color_(obj.color_) {};

	std::string getName() const;
	std::string getColor() const;

	void setName(const std::string&);
	void setColor(const std::string&);

	virtual void show() const;
};
#endif // !UNTITLED_FLOWER_H