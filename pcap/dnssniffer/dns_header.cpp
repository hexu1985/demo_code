#include "dns_header.h"

using std::string;

// 解析dns的question name,
// nameptr指向question开始,
// end为数据区结尾(防止数据截断造成处理越界),
// 如果解析成功返回, question name在原始数据中的长度,
// 否则返回-1表示错误,
// 解析出来的域名放在name中.
int dns_qname(const uint8_t *nameptr, const uint8_t *end, string &name)
{
	const uint8_t *p = nameptr;
	uint8_t len = *p++;
	if (len == 0)	// root domain
		name = ".";
	else
		name = "";
	while (len != 0 && p < end) {
		name.append((const char *) p, len);	// fetch subdomain
		p += len;	// move to next subdomain
		len = *p++;
		if (len != 0) name.push_back('.');
	}
	if (len == 0) {
		return p - nameptr;
	} else {
		return -1;
	}
}

Dns_question resolve_dns_question(const uint8_t *beg, const uint8_t *end,
	string &name)
{
	Dns_question q;
	q.qname_len = dns_qname(beg, end, name);
	q.qname_beg = (uint8_t *) beg;
	if (q.qname_len >= 0) {	// resolve error
		q.qtype = (uint16_t *) (q.qname_beg + q.qname_len);
		q.qclass = q.qtype+1;
	}
	return q;
}

