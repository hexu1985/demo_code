#ifndef __MYSTRING__INC
#define __MYSTRING__INC

class MyString {
public:
  MyString();
  ~MyString();
  void print();

private:
  void *raw;
};

#endif
