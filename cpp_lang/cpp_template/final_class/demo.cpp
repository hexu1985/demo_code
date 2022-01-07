
class Base {
public:
    Base() {}
    
};

class Derived: public Base {
public:
    Derived() {}
};

int main()
{
    Base b;
    Derived d;
    return 0;
}
