#ifndef __num_h
#define __num_h

struct Num
{
    Num(){}
    float get() const { return val; }
    void set(float val) { this->val = val; }
    float val;
};

#endif
