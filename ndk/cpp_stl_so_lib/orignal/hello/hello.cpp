#include <cstdlib>
#include <string>
#include <vector>

extern "C" {

__attribute__((visibility ("default")))
int print_hello()
{
	fprintf(stderr, "%s:%d, print_hello\n", __FILE__, __LINE__);
	fprintf(stderr, "%s:%d, std::vector<std::string> param_names;\n", __FILE__, __LINE__);
	std::vector<std::string> param_names;
	fprintf(stderr, "%s:%d, param_names.push_back(\"param\");\n", __FILE__, __LINE__);
	param_names.push_back("param");
	fprintf(stderr, "%s:%d, return CV_OK\n", __FILE__, __LINE__);
	return 0;
}

}

