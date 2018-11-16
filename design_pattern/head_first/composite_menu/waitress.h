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
};

#endif
