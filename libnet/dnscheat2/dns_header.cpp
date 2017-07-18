#include "dns_header.h"

using std::string;

// 解析dns的question name,
// nameptr指向question开始,
// end为数据区结尾(防止数据截断造成处理越界),
// 如果解析成功返回, question name在原始数据中的长度,
// 否则返回-1表示错误,
// 解析出来的域名放在name中.
int parser_dns_query(uint8_t *beg, uint8_t *end,
		string &qname, uint16_t *qtype, uint16_t *qclass)
{
	const uint8_t *p = beg;
	uint8_t len = *p++;
	if (len == 0)	// root domain
		qname = ".";
	else
		qname = "";
	while (len != 0 && p < end) {
		qname.append((const char *) p, len);	// fetch subdomain
		p += len;	// move to next subdomain
		len = *p++;
		if (len != 0) qname.push_back('.');
	}
	if (len != 0 || p+4 > end)	// qtype+qclass占4字节
		return -1;

	*qtype = *(uint16_t *)(p);
	*qclass = *(uint16_t *)(p+2);

	return p+4-beg;
}

