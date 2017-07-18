#include "httpresp.h"
#include "http_parser.h"

#include <stdint.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <string>

using std::vector;
using std::map;
using std::string;

bool httpresp_parse(uint8_t *beg, uint8_t *end, 
		struct Httpresp_header *httpresp_hdr)
{
   	uint8_t *mime_beg;

	// 解析response line
	if (!Http_parser::parse_response_line(beg, end, 
				httpresp_hdr->version, httpresp_hdr->status, httpresp_hdr->reason, 
				&mime_beg)) {
#ifndef NDEBUG
		printf("httpresp_parse error: resolve response line fault\n");
#endif
		return false;
	}

	// 解析http mime header
	map<string, string> mime_pairs;
	mime_pairs["Content-Type"] = "";
	mime_pairs["Content-Length"] = "";
	if (!Http_parser::parse_mime_header(mime_beg, end, mime_pairs)) {
#ifndef NDEBUG
		printf("httpresp_parse error: resolve response header fault\n");
#endif
		return false;
	}

	httpresp_hdr->content_type = mime_pairs["Content-Type"];
	httpresp_hdr->content_length = mime_pairs["Content-Length"];

	return true;
}

