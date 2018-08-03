#ifndef __duck_h
#define __duck_h

class Duck {
public: 
    virtual ~Duck() {}
    virtual void quack() = 0;
	virtual void fly() = 0;
};

#endif
