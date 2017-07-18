#ifndef __wget_h
#define __wget_h

#include <stdint.h>
#include <tr1/memory>
#include <string>

std::tr1::shared_ptr<std::string> wget(const char *httpget, int httpget_len,
		const char *server_host, uint16_t port);

#endif
