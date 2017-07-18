#include <iostream>
#include <ctime>
#include <vector>
#include <boost/pool/pool.hpp>
#include <boost/pool/object_pool.hpp>

using namespace std;
using namespace boost;

const int MAXLENGTH = 500000;

class A {
public:
    A()
    {
        m_i++;
    }

    ~A( )
    {
        m_i--;
    }

private:
    int m_i;
};

int main ( )
{
    object_pool<A> q;

    clock_t clock_begin = clock();
    for (int i = 0; i < MAXLENGTH; ++i)
    {
        A* a = q.construct();
        q.destroy(a);
    }

    clock_t clock_end = clock();
    cout<<"程序运行了 "<<clock_end-clock_begin<<" 个系统时钟"<<endl;

    clock_begin = clock();
    for (int i = 0; i < MAXLENGTH; ++i)
    {
        A* a = new A;
        delete a;
    }
    clock_end = clock();
    cout<<"程序运行了 "<<clock_end-clock_begin<<" 个系统时钟"<<endl;

    return 0;
}
