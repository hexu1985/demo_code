#ifndef __observer_h
#define __observer_h

class Observer {
public:
    virtual void update(float temp, float humidity, float pressure) = 0;
};

#endif
