#include "menu.h"

MenuComponent &CompositeIterator::next() {
	if (hasNext()) {
		auto iterator = stack.top();
		MenuComponent &component = iterator->next();
		if (dynamic_cast<Menu *>(&component)) {
			stack.push(component.createIterator());
		} 
		return component;
	} else {
		return null;
	}
}

