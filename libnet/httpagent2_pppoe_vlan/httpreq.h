#ifndef HTTPREQ_H
#define HTTPREQ_H

#include <stdint.h>
#include <string>

struct Httpreq_header {
	std::string method;
	std::string uri;
	std::string version;
	std::string host;
	std::string user_agent;
};

bool httpreq_parse(uint8_t *beg, uint8_t *end, 
		struct Httpreq_header *httpreq_hdr);

#endif
