#ifndef __composite_iterator_h
#define __composite_iterator_h

#include <stack>
#include "iterator.h"
#include "null_component.h"

class CompositeIterator: public Iterator {
private:
	std::stack<std::shared_ptr<Iterator>> stack;

public:
	CompositeIterator(std::shared_ptr<Iterator> iterator) {
		stack.push(iterator);
	}
   
	MenuComponent &next() override;
  
	bool hasNext() override {
		if (stack.empty()) {
			return false;
		} else {
			auto iterator = stack.top();
			if (!iterator->hasNext()) {
				stack.pop();
				return hasNext();
			} else {
				return true;
			}
		}
	}
   
	void remove() {
		throw UnsupportedOperationException();
	}
};

#endif
