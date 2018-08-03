#ifndef __mallar_duck_h
#define __mallar_duck_h

#include "duck.h"

class MallardDuck: public Duck {
public:
	void quack() override;
 
	void fly() override; 
};

#endif
