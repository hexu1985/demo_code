#ifndef __pancake_house_menu_iterator_h
#define __pancake_house_menu_iterator_h

#include <vector>
#include "iterator.h"

class PancakeHouseMenuIterator: public Iterator {
private:
	std::vector<MenuItem> *items;
	int position = 0;

public:  
	PancakeHouseMenuIterator(std::vector<MenuItem> *items) {
		this->items = items;
	}
 
	MenuItem &next() {
		MenuItem &object = items->at(position);
		position = position + 1;
		return object;
	}
 
	bool hasNext() {
		if (position >= items->size()) {
			return false;
		} else {
			return true;
		}
	}
};

#endif
