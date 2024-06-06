#include <iostream>
 
// Every object of type struct_float will be aligned
// to alignof(float) boundary (usually 4):
struct alignas(float) struct_float
{
    // your definition here
};
 
// Every object of type sse_t will be aligned to 32-byte boundary:
struct alignas(32) sse_t
{
    float sse_data[4];
};
 
// The array "cacheline" will be aligned to 64-byte boundary:
using cacheline_t = alignas(64) char[64];
cacheline_t cacheline;
 
int main()
{
    struct default_aligned
    {
        float data[4];
    } a, b, c;
    sse_t x, y, z;
 
    std::cout
        << "alignof(struct_float) = " << alignof(struct_float) << '\n'
        << "sizeof(sse_t) = " << sizeof(sse_t) << '\n'
        << "alignof(sse_t) = " << alignof(sse_t) << '\n'
        << "alignof(cacheline_t) = " << alignof(cacheline_t) << '\n'
        << "alignof(cacheline) = " << alignof(decltype(cacheline)) << '\n'
        << std::hex << std::showbase
        << "&a: " << &a << "\n"
           "&b: " << &b << "\n"
           "&c: " << &c << "\n"
           "&x: " << &x << "\n"
           "&y: " << &y << "\n"
           "&z: " << &z << '\n';
}
