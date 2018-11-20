#ifndef __null_iterator_h
#define __null_iterator_h

#include "iterator.h"
#include "null_component.h"
#include "unsupported_operation_exception.h"
  
class NullIterator: public Iterator {
public:   
	MenuComponent &next() override {
		return null;
	}
  
	bool hasNext() override {
		return false;
	}
};

#endif
