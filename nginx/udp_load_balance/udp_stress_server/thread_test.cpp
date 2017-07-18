#include <iostream>
#include "thread.h"

void print_int(int i)
{
	std::cout << __func__ << "(" << i << ")" << std::endl;
}

void print_string(std::string str)
{
	std::cout << __func__ << "(" << str << ")" << std::endl;
}

class Foo {
	int n_;
public:
	Foo(int n): n_(n) {}

	void print()
	{
		std::cout << "Foo::" << __func__ << "(" << n_++ << ")" << std::endl;
	}
};

void process_exit()
{
	std::cout << "task to stop process thread" << std::endl;
	pthread_exit(NULL);
}

class Base {
public:
    virtual void print() 
    {
        std::cout << "Base::print" << std::endl;
    }
};

class Derived_A : public Base {
public:
    virtual void print() 
    {
        std::cout << "Derived_A::print" << std::endl;
    }
};

class Derived_B : public Base {
public:
    virtual void print() 
    {
        std::cout << "Derived_B::print" << std::endl;
    }
};

int main()
{
	Foo foo(1);
    Thread mythread("test");
    mythread.start();

	auto task_queue = mythread.get_task_queue();
	for (int i = 0; i < 10; i++) {
		task_queue->push_task(make_task(print_int, i));
		task_queue->push_task(make_task(print_string, std::string("hello")));
		task_queue->push_task(make_task(&Foo::print, &foo));
	}
    Base base;
    Derived_A derived_a;
    Derived_B derived_b;

    Base *p1 = &base;
    Base *p2 = &derived_a;
    Base *p3 = &derived_b;

    task_queue->push_task(make_task(&Base::print, p1));
    task_queue->push_task(make_task(&Base::print, p2));
    task_queue->push_task(make_task(&Base::print, p3));

    mythread.stop();
	return 0;
}

