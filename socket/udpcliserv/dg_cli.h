#ifndef __unp_dg_cli_h
#define __unp_dg_cli_h

#include "wrapsock.h"
#include "wrapstdio.h"
#include "wraplib.h"

void dg_cli(FILE *, int, const sockaddr *, socklen_t);

#endif
