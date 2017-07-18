#include "httpget.h"

#include <stdint.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;

namespace {

string strip(const string &str)
{
	size_t beg = str.find_first_not_of(' ');
	size_t end = str.find_last_not_of(' ');
	return str.substr(beg, end-beg+1);
}

uint8_t *find_next_crlf(uint8_t *beg, uint8_t *end)
{
	while (beg < end) {
		if (*beg++ == '\r' && *beg++ == '\n')
			return beg-2;
	}
	return end;
}

// 查找下一个\r\n,
// 并且记录sep字符所在位置, 并放入sep_pos_list
uint8_t *find_next_crlf(uint8_t *beg, uint8_t *end, uint8_t sep, vector<uint8_t *> &sep_pos_list)
{
	sep_pos_list.clear();
	while (beg < end) {
		if (*beg == sep) {
			sep_pos_list.push_back(beg);
		} 
		if (*beg == '\r' && *(beg+1) == '\n') {
			return beg;
		}
		beg++;
	}
	return end;
}

// 解析HTTP Request Line
// 例如
// GET / HTTP/1.1
bool resolve_request_line(uint8_t *beg, uint8_t *end,
	string &method, string &uri, string &version, uint8_t **next_line_beg)
{
	vector<uint8_t *> sep_pos_list;
	uint8_t *line_beg = beg;
   	uint8_t *line_end = find_next_crlf(beg, end, ' ', sep_pos_list);
	if (line_end == end) {
#ifndef NDEBUG
		printf("resolve request line error: no found \\r\\n\n");
#endif
		return false;
	}

	if (sep_pos_list.size() != 2) {
#ifndef NDEBUG
		printf("resolve request line error: invalid format for '%s'",
				string(line_beg, line_end).c_str());
#endif
		return false;
	}

	method.assign(line_beg, sep_pos_list[0]);
	uri.assign(sep_pos_list[0]+1, sep_pos_list[1]);
	version.assign(sep_pos_list[1], line_end);

	*next_line_beg = line_end+2;
	return true;
}

// 解析HTTP Request Header
// 提取host和user-agent
// 例如
// Host: www.sina.com.cn
// User-Agent: Wget/1.16.3 (linux-gnu)
bool resolve_request_header(uint8_t *beg, uint8_t *end,
	string &host, string &user_agent)
{
	uint8_t *line_beg;
   	uint8_t *line_end;
	vector<uint8_t *> sep_pos_list;
	line_beg = beg;
	host = "";
	user_agent = "";
	string key, value;
	while (true) {
		line_end = find_next_crlf(line_beg, end, ':', sep_pos_list);
		if (line_end == end) {
#ifndef NDEBUG
			printf("resolve_request_header error: not complete header\n");
#endif
			return false;
		}
		if (line_end == line_beg) // "\r\n\r\n"表示http头结束
			return true;
		if (sep_pos_list.empty()) {
#ifndef NDEBUG
			printf("resolve_request_header error: invalid header: %s\n",
				string(line_beg, line_end).c_str());
#endif
			return false;
		}
		key.assign(line_beg, sep_pos_list[0]);
		value.assign(sep_pos_list[0]+1, line_end);

		if (key == "Host") {
			host = strip(value);
		} else if (key == "User-Agent") {
			user_agent = strip(value);
		}
		line_beg = line_end+2;
	}
}

}	// namespace 

bool httpget_unpack(uint8_t *beg, uint8_t *end, 
	struct Httpget_header *httpget_hdr)
{
   	uint8_t *new_beg;

	// 解析request line
	if (!resolve_request_line(beg, end, httpget_hdr->method, httpget_hdr->uri, 
			httpget_hdr->version, &new_beg)) {
#ifndef NDEBUG
		printf("httpget_unpack error: resolve request line fault\n");
#endif
		return false;
	}

#if 0
	if (httpget_hdr->method != "GET") {
#ifndef NDEBUG
		printf("httpget_unpack error: not GET method, actual method is %s\n",
			httpget_hdr->method.c_str());
#endif
		return false;
	}
#endif

	// 解析http get body
	if (!resolve_request_header(new_beg, end, httpget_hdr->host,
			httpget_hdr->user_agent)) {
#ifndef NDEBUG
		printf("httpget_unpack error: resolve request header fault\n");
#endif
		return false;
	}

	return true;
}

