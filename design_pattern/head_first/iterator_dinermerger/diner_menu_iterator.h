#ifndef __diner_menu_iterator_h
#define __diner_menu_iterator_h

#include "iterator.h"

class DinerMenuIterator: public Iterator {
private:
	MenuItem *items;
	int position = 0;
	int numberOfItems;
 
public: 
	DinerMenuIterator(MenuItem *items, int numberOfItems) {
		this->items = items;
		this->numberOfItems = numberOfItems;
	}
 
	MenuItem &next() {
		MenuItem &menuItem = items[position];
		position = position + 1;
		return menuItem;
	}
 
	bool hasNext() {
		if (position >= numberOfItems) {
			return false;
		} else {
			return true;
		}
	}
};

#endif
