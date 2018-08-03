#ifndef __turkey_h
#define __turkey_h

class Turkey {
public:
    virtual ~Turkey() {}
	virtual void gobble() = 0;
	virtual void fly() = 0;
};

#endif
