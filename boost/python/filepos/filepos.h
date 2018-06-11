#ifndef __filepos_h
#define __filepos_h

class FilePos
{
public:
    FilePos() :len(0) {}
    operator double()const { return len; };//重载类型转换符
    int len;
};

// operator 方法

FilePos operator+(FilePos pos, int a);

FilePos operator+(int a, FilePos pos);

int operator-(FilePos pos1, FilePos pos2);

FilePos operator-(FilePos pos, int a);

FilePos &operator+=(FilePos & pos, int a);

FilePos &operator-=(FilePos & pos, int a);

bool operator<(FilePos  pos1, FilePos pos2);

//特殊的方法
FilePos pow(FilePos pos1, FilePos pos2);

FilePos abs(FilePos pos);

std::ostream& operator<<(std::ostream& out, FilePos pos);

#endif
