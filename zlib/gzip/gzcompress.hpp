#ifndef GZCOMPRESS_INC
#define GZCOMPRESS_INC

#include <string>
#include <zlib/zlib.h>

int GzipCompress(const std::string &from, std::string &out);
int GzipUnCompress(const std::string &compress_data, std::string &ori_data); 

#endif

