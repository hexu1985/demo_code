#include "error.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>        /* ANSI C header file */
#include <iostream>
#include <string>
#include <system_error>

static std::string err_doit(int, const char *, va_list);

/* Nonfatal error related to system call
 * Print message and return */

void
err_ret(const char *fmt, ...)
{
    va_list ap;

    std::string err_msg;
    va_start(ap, fmt);
    err_msg = err_doit(1, fmt, ap);
    va_end(ap);
    err_msg += '\n';
    std::cerr << err_msg;
    return;
}

/* Fatal error related to system call
 * Print message and terminate */

void
err_sys(const char *fmt, ...)
{
    va_list ap;

    std::error_code err_code(errno, std::generic_category());
    std::string err_msg;
    va_start(ap, fmt);
    err_msg = err_doit(0, fmt, ap);
    va_end(ap);
    throw std::system_error(err_code, err_msg);
}

/* Fatal error related to system call
 * Print message, dump core, and terminate */

void
err_dump(const char *fmt, ...)
{
    va_list ap;

    std::string err_msg;
    va_start(ap, fmt);
    err_msg = err_doit(1, fmt, ap);
    va_end(ap);
    err_msg += '\n';
    std::cerr << err_msg;
    abort();        /* dump core and terminate */
    exit(1);        /* shouldn't get here */
}

/* Nonfatal error unrelated to system call
 * Print message and return */

void
err_msg(const char *fmt, ...)
{
    va_list ap;

    std::string err_msg;
    va_start(ap, fmt);
    err_msg = err_doit(0, fmt, ap);
    va_end(ap);
    err_msg += '\n';
    std::cerr << err_msg;
    return;
}

/* Fatal error unrelated to system call
 * Print message and terminate */

void
err_quit(const char *fmt, ...)
{
    va_list ap;

    std::string err_msg;
    va_start(ap, fmt);
    err_msg = err_doit(0, fmt, ap);
    va_end(ap);
    throw std::runtime_error(err_msg);
}

/* Print message and return to caller
 * Caller specifies "errnoflag" and "level" */

static std::string
err_doit(int errnoflag, const char *fmt, va_list ap)
{
    const int MAXLINE = 4096;
    int     errno_save, n;
    char    buf[MAXLINE + 1];

    errno_save = errno;        /* value caller might want printed */
    vsnprintf(buf, MAXLINE, fmt, ap);    /* safe */
    n = strlen(buf);
    if (errnoflag)
        snprintf(buf + n, MAXLINE - n, ": %s", strerror(errno_save));
    return std::string(buf);
}

