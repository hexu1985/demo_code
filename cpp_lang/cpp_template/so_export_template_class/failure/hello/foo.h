#ifndef __FOO_INC
#define __FOO_INC

template <typename T>
class __attribute__ ((visibility("default")))Foo {
public:
  Foo();
  ~Foo();

  void print();

private:
  void *pimpl;
};

#endif
