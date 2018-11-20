#ifndef __iterator_h
#define __iterator_h

class MenuComponent;

class Iterator {
public:
    virtual ~Iterator() {}
	virtual bool hasNext() = 0;
	virtual MenuComponent &next() = 0;
};

#endif
