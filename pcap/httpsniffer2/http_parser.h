#ifndef HTTP_PARSER_H
#define HTTP_PARSER_H

#include <stdint.h>
#include <string>
#include <map>

// Http header解析的工具类
struct Http_parser {
	// 解析HTTP Request Line
	// 例如
	// GET / HTTP/1.1
	// 返回下一行开始位置
	static bool parse_request_line(uint8_t *beg, uint8_t *end, 
			std::string &method, std::string &uri, std::string &version, 
			uint8_t **next_line_beg);
	
	// 解析HTTP Response Line
	// 例如
	// HTTP/1.1 200 OK
	// 返回下一行开始位置
	static bool parse_response_line(uint8_t *beg, uint8_t *end, 
			std::string &version, std::string &status, std::string &reason, 
			uint8_t **next_line_beg);
	
	// 解析HTTP MIME Header
	// 例如: 提取host和user-agent
	// map<string, string>里insert: {"Host": "" }, {"User-Agent": ""}
	// 结果集也是在map<string, string>里, 例如
	// {"Host": "www.sina.com.cn"}
	// {"User-Agent": "Wget/1.16.3 (linux-gnu)"}
	static bool parse_mime_header(uint8_t *beg, uint8_t *end, 
			std::map<std::string, std::string> &mime_pairs);
};

#endif
