#ifndef __httpget_h
#define __httpget_h

#include <stdint.h>
#include <string>

struct Httpget_header {
	std::string method;
	std::string uri;
	std::string version;
	std::string host;
	std::string user_agent;
};

bool httpget_unpack(uint8_t *beg, uint8_t *end, 
	struct Httpget_header *httpget_hdr);

#endif
