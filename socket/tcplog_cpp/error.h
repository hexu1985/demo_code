#ifndef	__unp_error_h
#define __unp_error_h

[[ noreturn ]] void err_dump(const char *, ...);
void err_msg(const char *, ...);
[[ noreturn ]] void err_quit(const char *, ...);
void err_ret(const char *, ...);
[[ noreturn ]] void err_sys(const char *, ...);

#endif

