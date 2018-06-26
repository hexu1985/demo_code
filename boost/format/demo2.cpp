#include <iostream>
#include <boost/format.hpp>

using namespace std;
using namespace boost;

int main()
{
    format fmt("%05d\n%-8.3f\n% 10s\n%05X\n");
    cout << fmt %62 % 2.236 % "123456789" % 48;

    format fmt2("%|05d|\n%|-8.3f|\n%| 10s|\n%|05X|\n");
    cout << fmt2 %62 % 2.236 % "123456789" % 48;

    const format fmt3("%10d %020.8f %010X %10.5e\n");
    cout << format(fmt3) %62 % 2.236 % 255 % 0.618;

    return 0;
}
