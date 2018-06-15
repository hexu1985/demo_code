#include <iostream>
#include "boost/filesystem.hpp"
namespace fs = boost::filesystem;

int main()
{
	fs::path p = "/foo/bar.jpeg";
	std::cout << "Was: " << p << '\n';
	p.replace_extension(".jpg");
	std::cout << "Now: " << p << '\n';
}
