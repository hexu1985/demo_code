#ifndef __null_component_h
#define __null_component_h

#include "menu_component.h"

class NullComponent: public MenuComponent {
	std::shared_ptr<Iterator> createIterator() override {
		return nullptr;
	}	
};

extern NullComponent null;

#endif
