#include <tuple>

template <typename T, typename U> void my_func(T &&t, U &&u) {}

int main(int argc, char *argv[]) {

  std::tuple<int, float> my_tuple;

  std::apply([](auto &&... args) { my_func(args...); }, my_tuple);

  return 0;
}
