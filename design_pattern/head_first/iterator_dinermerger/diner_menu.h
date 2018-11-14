#ifndef __diner_menu_h
#define __diner_menu_h

#include <string>
#include <memory>
#include <iostream>
#include "menu_item.h"
#include "diner_menu_iterator.h"

class DinerMenu: public Menu {
private:
	static const int MAX_ITEMS = 6;
	int numberOfItems = 0;
	MenuItem *menuItems;
  
public:
	DinerMenu() {
		menuItems = new MenuItem[MAX_ITEMS];
 
		addItem("Vegetarian BLT",
			"(Fakin') Bacon with lettuce & tomato on whole wheat", true, 2.99);
		addItem("BLT",
			"Bacon with lettuce & tomato on whole wheat", false, 2.99);
		addItem("Soup of the day",
			"Soup of the day, with a side of potato salad", false, 3.29);
		addItem("Hotdog",
			"A hot dog, with saurkraut, relish, onions, topped with cheese",
			false, 3.05);
		addItem("Steamed Veggies and Brown Rice",
			"Steamed vegetables over brown rice", true, 3.99);
		addItem("Pasta",
			"Spaghetti with Marinara Sauce, and a slice of sourdough bread",
			true, 3.89);
	}

	~DinerMenu() 
	{
		delete [] menuItems;
	}
  
	void addItem(std::string name, std::string description, 
	                     bool vegetarian, double price) 
	{
		if (numberOfItems >= MAX_ITEMS) {
			std::cout << "Sorry, menu is full!  Can't add item to menu\n";
		} else {
			menuItems[numberOfItems] = MenuItem(name, description, vegetarian, price);
			numberOfItems = numberOfItems + 1;
		}
	}
 
	MenuItem *getMenuItems() {
		return menuItems;
	}
  
	std::shared_ptr<Iterator> createIterator() {
		return std::make_shared<DinerMenuIterator>(menuItems, numberOfItems);
	}
 
	// other menu methods here
	int length() {
		return numberOfItems;
	}
};

#endif
