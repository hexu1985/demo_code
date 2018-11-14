#ifndef __iterator_h
#define __iterator_h

class MenuItem;

class Iterator {
public:
    virtual ~Iterator() {}
	virtual bool hasNext() = 0;
	virtual MenuItem &next() = 0;
};

#endif
