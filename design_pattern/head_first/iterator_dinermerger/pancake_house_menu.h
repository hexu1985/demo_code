#ifndef __pancake_house_menu_h
#define __pancake_house_menu_h

#include <vector>
#include <memory>
#include "menu.h"
#include "menu_item.h"
#include "pancake_house_menu_iterator.h"

class PancakeHouseMenu: public Menu {
private:
	std::vector<MenuItem> menuItems;

public:
	PancakeHouseMenu() {
		addItem("K&B's Pancake Breakfast", 
			"Pancakes with scrambled eggs, and toast", 
			true,
			2.99);
 
		addItem("Regular Pancake Breakfast", 
			"Pancakes with fried eggs, sausage", 
			false,
			2.99);
 
		addItem("Blueberry Pancakes",
			"Pancakes made with fresh blueberries",
			true,
			3.49);
 
		addItem("Waffles",
			"Waffles, with your choice of blueberries or strawberries",
			true,
			3.59);
	}

	void addItem(std::string name, std::string description,
	                    bool vegetarian, double price)
	{
		menuItems.emplace_back(name, description, vegetarian, price);
	}
 
	std::vector<MenuItem> &getMenuItems() {
		return menuItems;
	}
  
	std::shared_ptr<Iterator> createIterator() {
		return std::make_shared<PancakeHouseMenuIterator>(&menuItems);
	}
  
	std::string toString() {
		return "Objectville Pancake House Menu";
	}

	// other menu methods here
};

#endif
