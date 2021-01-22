#ifndef EXC_H
#define EXC_H

#include <stdexcept>

struct grab_exception : std::runtime_error
{
	grab_exception (std::string const& str) :
		runtime_error(str)
	{}
};

#endif
