#ifndef __waitress_h
#define __waitress_h

#include <memory>
#include "menu_component.h"

class Waitress {
private:
	std::shared_ptr<MenuComponent> allMenus;
 
public:
	Waitress(std::shared_ptr<MenuComponent> allMenus) {
		this->allMenus = allMenus;
	}
 
	void printMenu() {
		allMenus->print();
	}

	void printVegetarianMenu() {
		auto iterator = allMenus->createIterator();

		std::cout << "\nVEGETARIAN MENU\n----" << '\n';
		while (iterator->hasNext()) {
			MenuComponent &menuComponent = 
					iterator->next();
			try {
				if (menuComponent.isVegetarian()) {
					menuComponent.print();
				}
			} catch (const UnsupportedOperationException &e) {}
		}
	}
};

#endif
