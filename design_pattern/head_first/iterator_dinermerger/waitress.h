#ifndef __waitress_h
#define __waitress_h

#include <memory>
#include "pancake_house_menu.h"
#include "diner_menu.h"

class Waitress {
private:
	std::shared_ptr<PancakeHouseMenu> pancakeHouseMenu;
	std::shared_ptr<DinerMenu> dinerMenu;
 
public:
	Waitress(std::shared_ptr<PancakeHouseMenu> pancakeHouseMenu, std::shared_ptr<DinerMenu> dinerMenu) {
		this->pancakeHouseMenu = pancakeHouseMenu;
		this->dinerMenu = dinerMenu;
	}
 
	void printMenu() {
		auto pancakeIterator = pancakeHouseMenu->createIterator();
		auto dinerIterator = dinerMenu->createIterator();

		std::cout << "MENU\n----\nBREAKFAST" << '\n';
		printMenu(pancakeIterator);
		std::cout << "\nLUNCH" << '\n';
		printMenu(dinerIterator);
	}
 
	void printMenu(std::shared_ptr<Iterator> iterator) {
		while (iterator->hasNext()) {
			MenuItem &menuItem = iterator->next();
			std::cout << menuItem.getName() << ", "
						<< menuItem.getPrice() << " -- "
						<< menuItem.getDescription()
						<< '\n';
		}
	}
 
	void printVegetarianMenu() {
		printVegetarianMenu(pancakeHouseMenu->createIterator());
		printVegetarianMenu(dinerMenu->createIterator());
	}
 
	bool isItemVegetarian(std::string name) {
		auto breakfastIterator = pancakeHouseMenu->createIterator();
		if (isVegetarian(name, breakfastIterator)) {
			return true;
		}
		auto dinnerIterator = dinerMenu->createIterator();
		if (isVegetarian(name, dinnerIterator)) {
			return true;
		}
		return false;
	}


	void printVegetarianMenu(std::shared_ptr<Iterator> iterator) {
		while (iterator->hasNext()) {
			MenuItem &menuItem = iterator->next();
			if (menuItem.isVegetarian()) {
				std::cout << menuItem.getName()
							<< "\t\t" << menuItem.getPrice() << '\n'
							<< "\t" << menuItem.getDescription()
							<< '\n';
			}
		}
	}

	bool isVegetarian(std::string name, std::shared_ptr<Iterator> iterator) {
		while (iterator->hasNext()) {
			MenuItem &menuItem = iterator->next();
			if (menuItem.getName() == name) {
				if (menuItem.isVegetarian()) {
					return true;
				}
			}
		}
		return false;
	}
};

#endif
