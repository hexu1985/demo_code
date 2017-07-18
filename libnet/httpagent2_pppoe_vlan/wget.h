#ifndef WGET_H
#define WGET_H

#include <stdint.h>
#include <tr1/memory>
#include <string>

std::tr1::shared_ptr<std::string> wget_local(const char *httpget, int httpget_len);

#endif
