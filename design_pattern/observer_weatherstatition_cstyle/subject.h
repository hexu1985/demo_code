#ifndef __subject_h
#define __subject_h

class Observer; 

class Subject {
public:
    virtual void register_observer(Observer *o) = 0;
    virtual void remove_observer(Observer *o) = 0;
    virtual void notify_observers() = 0;
};

#endif
