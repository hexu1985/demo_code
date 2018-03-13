#include <iostream>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>

using namespace std;
using namespace boost;

void to_interrupt(int x)
try
{
    for (int i = 0;i < x; ++i)
    {
        this_thread::sleep_for(chrono::seconds(1));
        cout << i << endl;
        this_thread::interruption_point();
    }
}
catch(const thread_interrupted& )
{
    cout << "thread_interrupted" << endl;
}

int main(int argc, char *argv[])
{
    thread t(to_interrupt,10);
    this_thread::sleep_for(chrono::seconds(3));

    t.interrupt();
    assert(t.interruption_requested());

    t.join();
    return 0;
}
