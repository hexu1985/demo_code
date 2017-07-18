#include <iostream>
#include <ctime>
#include <vector>
#include <boost/pool/pool.hpp>
#include <boost/pool/object_pool.hpp>

using namespace std;
using namespace boost;

int main(int argc, char* argv[])
{
    boost::pool<> pl(1024*1024);
    clock_t clock_begin = clock();
    int iLength = 0;
    for (int i = 0; ;++i)
    {
        void* p = pl.malloc();
        if (p == NULL)
        {
            break;
        }
        ++iLength;
    }
    clock_t clock_end = clock();
    cout<<"共申请了"<<iLength<<"M内存,程序运行了"<<clock_end-clock_begin<<" 个系统时钟"<<endl;

    clock_begin = clock();
    iLength = 0;
    boost::pool<> pl2(1024*1024);
    for (int i = 0; ;++i)
    {
        void* p = pl2.malloc();
        if (p == NULL)
        {
            break;
        }
        ++iLength;
    }
    clock_end = clock();
    cout<<"又申请了"<<iLength<<"M内存,程序运行了"<<clock_end-clock_begin<<" 个系统时钟"<<endl;

    return 0;
}
