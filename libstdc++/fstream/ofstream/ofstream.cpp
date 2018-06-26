// ofstream constructor.
#include <fstream>      // std::ofstream

int main () {

  std::ofstream ofs ("test.txt", std::ofstream::out);

  ofs << "lorem ipsum";

  ofs.close();

  return 0;
}
