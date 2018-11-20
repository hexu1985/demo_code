#ifndef __unsupported_operation_exception_h
#define __unsupported_operation_exception_h

#include <stdexcept>

class UnsupportedOperationException: public std::logic_error {
public:
	UnsupportedOperationException(): std::logic_error("unsupported operation") {}
};

#endif
