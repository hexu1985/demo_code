#ifndef __wild_turkey_h
#define __wild_turkey_h

#include "turkey.h"

class WildTurkey: public Turkey {
public:
	void gobble() override;
 
	void fly() override;
};

#endif
