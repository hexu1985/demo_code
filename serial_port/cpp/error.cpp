#include	"error.h"

#include	<stdarg.h>		/* ANSI C header file */
#include    <string>

SystemError::SystemError(const std::string &what_arg, int error_code):
    std::runtime_error(what_arg), error_code_(error_code)
{
}

int SystemError::code() const
{
    return error_code_;
}

static std::string err_doit(int, const char *, va_list);

/* Nonfatal error related to system call
 * Print message and return */

void
err_ret(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(1, fmt, ap);
	va_end(ap);
	return;
}

/* Fatal error related to system call
 * Print message and terminate */

void
err_sys(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
    std::string err_msg = err_doit(1, fmt, ap);
	va_end(ap);
    throw SystemError(err_msg, errno);
}

/* Fatal error related to system call
 * Print message, dump core, and terminate */

void
err_dump(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(1, fmt, ap);
	va_end(ap);
	abort();		/* dump core and terminate */
	exit(1);		/* shouldn't get here */
}

/* Nonfatal error unrelated to system call
 * Print message and return */

void
err_msg(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(0, fmt, ap);
	va_end(ap);
	return;
}

/* Fatal error unrelated to system call
 * Print message and terminate */

void
err_quit(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
    std::string err_msg = err_doit(0, fmt, ap);
	va_end(ap);
    throw std::runtime_error(err_msg);
}

/* Print message and return to caller
 * Caller specifies "errnoflag" and "level" */

static std::string
err_doit(int errnoflag, const char *fmt, va_list ap)
{
    const int MAXLINE = 4096;
	int		errno_save, n;
	char	buf[MAXLINE + 1];
    std::string err_msg;

	errno_save = errno;		/* value caller might want printed */
	vsnprintf(buf, MAXLINE, fmt, ap);	/* safe */
	n = strlen(buf);
	if (errnoflag)
		snprintf(buf + n, MAXLINE - n, ": %s", strerror(errno_save));
    err_msg = buf;
	strcat(buf, "\n");

    fflush(stdout);		/* in case stdout and stderr are the same */
    fputs(buf, stderr);
    fflush(stderr);
	return err_msg;
}
