#ifndef __turkey_adapter_h
#define __turkey_adapter_h

#include <memory>
#include "duck.h"
#include "turkey.h"

class TurkeyAdapter: public Duck {
private:
    std::shared_ptr<Turkey> turkey;
 
public:
	TurkeyAdapter(std::shared_ptr<Turkey> turkey); 
    
	void quack() override;
  
	void fly() override;
};

#endif
