#ifndef __menu_component_h
#define __menu_component_h

#include <string>
#include <memory>
#include "unsupported_operation_exception.h"

class Iterator;

class MenuComponent {
public:   
	virtual void add(std::shared_ptr<MenuComponent> menuComponent) {
		throw UnsupportedOperationException();
	}

	virtual void remove(std::shared_ptr<MenuComponent> menuComponent) {
		throw UnsupportedOperationException();
	}

	virtual std::shared_ptr<MenuComponent> getChild(int i) {
		throw UnsupportedOperationException();
	}
  
	virtual std::string getName() {
		throw UnsupportedOperationException();
	}

	virtual std::string getDescription() {
		throw UnsupportedOperationException();
	}

	virtual double getPrice() {
		throw UnsupportedOperationException();
	}

	virtual bool isVegetarian() {
		throw UnsupportedOperationException();
	}

	virtual std::shared_ptr<Iterator> createIterator() = 0;
  
	virtual void print() {
		throw UnsupportedOperationException();
	}
};

#endif
