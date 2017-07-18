#ifndef __print_h 
#define __print_h 

#include <string>

class Print {
private:
	std::string m_name;

public:
	explicit Print(const std::string &name): m_name(name) {}

	void hello();
};

#endif
