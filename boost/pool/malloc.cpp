#include <iostream>
#include <ctime>
#include <vector>
#include <boost/pool/pool.hpp>
#include <boost/pool/object_pool.hpp>

using namespace std;
using namespace boost;

int main(int argc, char* argv[])
{
    clock_t clock_begin = clock();
    int iLength = 0;
    for (int i = 0; ;++i)
    {
        void* p = malloc(1024*1024);
        if (p == NULL)
        {
            break;
        }
        ++iLength;
    }
    clock_t clock_end = clock();
    cout<<"共申请了"<<iLength<<"M内存,程序运行了"<<clock_end-clock_begin<<" 个系统时钟"<<endl;
    return 0;
}
