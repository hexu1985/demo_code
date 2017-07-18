#ifndef HTTPRESP_H
#define HTTPRESP_H

#include <stdint.h>
#include <string>

struct Httpresp_header {
	std::string version;
	std::string status;
	std::string reason;
	std::string content_type;
	std::string content_length;
};

bool httpresp_parse(uint8_t *beg, uint8_t *end, 
		struct Httpresp_header *httpresp_hdr);

#endif
