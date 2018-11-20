#ifndef __stl_iterator_adapter_h
#define __stl_iterator_adapter_h

#include "iterator.h"

template <typename iterator>
class StlIteratorAdapter: public Iterator {
private:
	iterator begin;
	iterator end;

public:
	StlIteratorAdapter(iterator begin, iterator end):
		begin(begin), end(end)
	{
	}

	bool hasNext() override
	{
		return begin != end;
	}

	MenuComponent &next() override
	{
		auto ptr = *begin;
		++begin;
		return *ptr;
	}
};

#endif
