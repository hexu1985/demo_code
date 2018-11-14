#ifndef __menu_item_h
#define __menu_item_h

#include <string>

class MenuItem {
private:
    std::string name;
    std::string description;
	bool vegetarian = false;
	double price = 0.0;
 
public:
	MenuItem()
	{
	}

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
  
	std::string getName() {
		return name;
	}
  
	std::string getDescription() {
		return description;
	}
  
	double getPrice() {
		return price;
	}
  
	bool isVegetarian() {
		return vegetarian;
	}

	std::string toString() {
		return (name + ", $" + std::to_string(price) + "\n   " + description);
	}
};

#endif
