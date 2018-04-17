#ifndef	__unp_error_h
#define __unp_error_h

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdexcept>
#include <string>

class SystemError: public std::runtime_error {
private:
    int error_code_;

public:
    SystemError(const std::string &what_arg, int error_code);
    int code() const;
};

void	 err_dump(const char *, ...);
void	 err_msg(const char *, ...);
void	 err_quit(const char *, ...);
void	 err_ret(const char *, ...);
void	 err_sys(const char *, ...);

#endif

