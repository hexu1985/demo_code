#include <iostream>
#include <ctime>
#include <vector>
#include <boost/pool/pool.hpp>
#include <boost/pool/object_pool.hpp>

using namespace std;
using namespace boost;

const int MAXLENGTH = 500000;

int main ( )
{
    boost::pool<> p(sizeof(int));

    clock_t clock_begin = clock();
    for (int i = 0; i < MAXLENGTH; ++i)
    {
        int * t = static_cast<int*>(p.malloc());
        p.free(t);
    }
    clock_t clock_end = clock();
    cout<<"程序运行了 "<<clock_end-clock_begin<<" 个系统时钟"<<endl;

    clock_begin = clock();
    for (int i = 0; i < MAXLENGTH; ++i)
    {
        int* t = new int;
        delete t;
    }
    clock_end = clock();
    cout<<"程序运行了 "<<clock_end-clock_begin<<" 个系统时钟"<<endl;

    return 0;
}
