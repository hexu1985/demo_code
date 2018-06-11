#include <iostream>
#include <cmath>
#include "filepos.h"

using namespace std;

FilePos operator+(FilePos pos, int a)
{
    pos.len = pos.len + a;
    return pos; //返回的是副本
}

FilePos operator+(int a, FilePos pos)
{
    pos.len = pos.len + a;
    return pos; //返回的是副本
}

int operator-(FilePos pos1, FilePos pos2)
{
    return (pos1.len - pos2.len);
}

FilePos operator-(FilePos pos, int a)
{
    pos.len = pos.len - a;
    return pos;
}

FilePos &operator+=(FilePos & pos, int a)
{
    pos.len = pos.len + a;
    return pos;
}

FilePos &operator-=(FilePos & pos, int a)
{
    pos.len = pos.len - a;
    return pos;
}

bool operator<(FilePos  pos1, FilePos pos2)
{
    if (pos1.len < pos2.len)
        return true;
    return false;
}


//特殊的方法

FilePos pow(FilePos pos1, FilePos pos2)
{
    FilePos res;
    res.len = std::pow(pos1.len, pos2.len);
    return res;

}
FilePos abs(FilePos pos)
{
    FilePos res;
    res.len = std::abs(pos.len);

    return res;
}

ostream& operator<<(ostream& out, FilePos pos)
{
    out << pos.len;
    return out;
}
