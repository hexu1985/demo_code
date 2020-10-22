#include <string>
#include <iostream>
#include <cstdlib>
#include "load_file.hpp"
#include "store_file.hpp"
#include "gzcompress.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " infile outfile" << "\n";
    exit(1);
  }

  auto content = load_file(argv[1]);
  std::string decompress_content;
  GzipUnCompress(content, decompress_content);
  store_file(argv[2], decompress_content);
  
  return 0;
}
