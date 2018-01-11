#ifndef __person_h
#define __person_h

#include <string>
#include <iostream>

class Person {
private:
    std::string lastName;
    std::string firstName;

public:
    Person(const std::string &lastName, const std::string &firstName) {
        this->lastName = lastName;
        this->firstName = firstName;
    }

    void print() {
        std::cout << firstName << " " << lastName << "\n";
    }
};

#endif
