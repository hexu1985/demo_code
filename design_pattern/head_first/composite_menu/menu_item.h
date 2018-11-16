#ifndef __menu_item_h
#define __menu_item_h

#include <string>
#include <iostream>
#include "menu_component.h"

class MenuItem: public MenuComponent {
private:
	std::string name;
	std::string description;
	bool vegetarian;
	double price;
    
public:
	MenuItem(std::string name, 
	                std::string description, 
	                bool vegetarian, 
	                double price) 
	{ 
		this->name = name;
		this->description = description;
		this->vegetarian = vegetarian;
		this->price = price;
	}
  
	std::string getName() override {
		return name;
	}
  
	std::string getDescription() override {
		return description;
	}
  
	double getPrice() override {
		return price;
	}
  
	bool isVegetarian() override {
		return vegetarian;
	}
  
	void print() override {
		std::cout << "  " << getName();
		if (isVegetarian()) {
			std::cout << "(v)";
		}
		std::cout << ", " << getPrice() << '\n'
					<< "     -- " << getDescription()
					<< '\n';
	}
};

#endif
