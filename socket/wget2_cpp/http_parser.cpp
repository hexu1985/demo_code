#include "http_parser.h"

#include <stdint.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>

using std::vector;
using std::string;
using std::map;

namespace {

string strip(const string &str)
{
    size_t beg = str.find_first_not_of(' ');
    size_t end = str.find_last_not_of(' ');
	if (beg == string::npos || end == string::npos)
		return "";
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

}	// namespace 

// 解析HTTP Request Line
// 例如
// GET / HTTP/1.1
// 返回下一行开始位置
bool Http_parser::parse_request_line(uint8_t *beg, uint8_t *end, 
		string &method, string &uri, string &version, 
		uint8_t **next_line_beg)
{
	vector<uint8_t *> sep_pos_list;
	uint8_t *line_beg = beg;
   	uint8_t *line_end = find_next_crlf(beg, end, ' ', sep_pos_list);
	if (line_end == end) {
#ifndef NDEBUG
		printf("parse request line error: no found \\r\\n\n");
#endif
		return false;
	}

	if (sep_pos_list.size() < 2) {
#ifndef NDEBUG
		printf("parse request line error: invalid format for '%s'\n",
				string(line_beg, line_end).c_str());
#endif
		return false;
	}

	method.assign(line_beg, sep_pos_list[0]);
	uri.assign(sep_pos_list[0]+1, sep_pos_list[1]);
	version.assign(sep_pos_list[1]+1, line_end);

	if (version.size() < 5 || version.substr(0, 5) != "HTTP/") {
#ifndef NDEBUG
		printf("parse request line error: invalid format for '%s'\n",
				string(line_beg, line_end).c_str());
#endif
		return false;
	}

	*next_line_beg = line_end+2;
	return true;
}

// 解析HTTP Response Line
// 例如
// HTTP/1.1 200 OK
// 返回下一行开始位置
bool Http_parser::parse_response_line(uint8_t *beg, uint8_t *end, 
		string &version, string &status, string &reason, 
		uint8_t **next_line_beg)
{
	vector<uint8_t *> sep_pos_list;
	uint8_t *line_beg = beg;
   	uint8_t *line_end = find_next_crlf(beg, end, ' ', sep_pos_list);
	if (line_end == end) {
#ifndef NDEBUG
		printf("parse response line error: no found \\r\\n\n");
#endif
		return false;
	}

	if (sep_pos_list.size() < 2) {
#ifndef NDEBUG
		printf("parse response line error: invalid format for '%s'\n",
				string(line_beg, line_end).c_str());
#endif
		return false;
	}

	version.assign(line_beg, sep_pos_list[0]);
	status.assign(sep_pos_list[0]+1, sep_pos_list[1]);
	reason.assign(sep_pos_list[1]+1, line_end);

	if (version.size() < 5 || version.substr(0, 5) != "HTTP/") {
#ifndef NDEBUG
		printf("parse request line error: invalid format for '%s'\n",
				string(line_beg, line_end).c_str());
#endif
		return false;
	}

	*next_line_beg = line_end+2;
	return true;
}

// 解析HTTP MIME Header
// 例如: 提取host和user-agent
// map<string, string>里insert: {"Host": "" }, {"User-Agent": ""}
// 结果集也是在map<string, string>里, 例如
// {"Host": "www.sina.com.cn"}
// {"User-Agent": "Wget/1.16.3 (linux-gnu)"}
bool Http_parser::parse_mime_header(uint8_t *beg, uint8_t *end, 
		map<string, string> &mime_pairs)
{
	uint8_t *line_beg;
   	uint8_t *line_end;
	vector<uint8_t *> sep_pos_list;
	line_beg = beg;
	string key, value;
	map<string, string>::iterator mime_pairs_iter;
	while (true) {
		line_end = find_next_crlf(line_beg, end, ':', sep_pos_list);
		if (line_end == end) {
#ifndef NDEBUG
			printf("parse_mime_header error: not complete header\n");
#endif
			return false;
		}
		if (line_end == line_beg) // "\r\n\r\n"表示http头结束
			return true;
		if (sep_pos_list.empty()) {
#ifndef NDEBUG
			printf("parse_mime_header error: invalid header: %s\n",
				string(line_beg, line_end).c_str());
#endif
			return false;
		}
		key.assign(line_beg, sep_pos_list[0]);
		value.assign(sep_pos_list[0]+1, line_end);

		// 提取指定key的value
		if ((mime_pairs_iter = mime_pairs.find(key)) != mime_pairs.end()) {
			mime_pairs_iter->second = strip(value);
		}
		line_beg = line_end+2;
	}
}


