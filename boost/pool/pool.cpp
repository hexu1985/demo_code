#include <iostream>
#include <ctime>
#include <vector>
#include <boost/pool/pool.hpp>
#include <boost/pool/object_pool.hpp>

using namespace std;
using namespace boost;

const int MAXLENGTH = 100000;

int main ( )
{
    boost::pool<> p(sizeof(int));
    int* vec1[MAXLENGTH];
    int* vec2[MAXLENGTH];

    clock_t clock_begin = clock();
    for (int i = 0; i < MAXLENGTH; ++i)
    {
        vec1[i] = static_cast<int*>(p.malloc());
    }
    for (int i = 0; i < MAXLENGTH; ++i)
    {
        p.free(vec1[i]);
        vec1[i] = NULL;
    }

    clock_t clock_end = clock();
    cout<<"程序运行了 "<<clock_end-clock_begin<<" 个系统时钟"<<endl;

    clock_begin = clock();
    for (int i = 0; i < MAXLENGTH; ++i)
    {
        vec2[i] = new int;
    }
    for (int i = 0; i < MAXLENGTH; ++i)
    {
        delete vec2[i];
        vec2[i] = NULL;
    }

    clock_end = clock();
    cout<<"程序运行了 "<<clock_end-clock_begin<<" 个系统时钟"<<endl;

    return 0;
}
