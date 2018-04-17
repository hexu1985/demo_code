#include <iostream>

#pragma pack(1)
struct S1 {
    long a;
    char b;
    int c;
    short d;
};
#pragma pack()

struct S2 {
    long a;
    char b;
    int c;
    short d;
};

using namespace std;

int main() 
{
    cout << "use pragma pack(1), sizeof (S1): " << sizeof (S1) << endl; 
    cout << "default aligning, sizeof (S2): " << sizeof (S2) << endl; 
    return 0;
}
