#ifndef _FUN_H_  
#define _FUN_H_  

#include <stdio.h>

// A simple monotonic counter.  
class Counter {  
private:  
    int counter_;  
  
public:  
    // Creates a counter that starts at 0.  
    Counter() : counter_(0) {}  
  
    // Returns the current counter value, and increments it.  
    int Increment();  
  
    // Prints the current counter value to STDOUT.  
    void Print() const;  
};  
  
#endif//_FUN_H_  
