#ifndef __duck_adapter_h
#define __duck_adapter_h

#include "turkey.h"
#include "duck.h"
#include <memory>
#include <random>

class DuckAdapter: public Turkey {
private:
    std::shared_ptr<Duck> duck;
    std::shared_ptr<std::minstd_rand0> rand;
 
public:
	DuckAdapter(std::shared_ptr<Duck> duck);
    
	void gobble() override;
  
	void fly() override; 
};

#endif
