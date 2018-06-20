#ifdef USE_GLOG
#include    "glog/logging.h"
#endif

#include <ctype.h>
#include <iomanip>
#include <iostream>
#include <sstream>

void dump_data(const std::string &str, const char *data, int length) {
    std::ostringstream os;

    os << str << ", data len: " << length << "\n";

    os << "ascii: ";
    for (int i = 0; i < length; i++) {
        os << " " << (isprint(data[i]) ? data[i] : '.') << " ";
    }
    os << "\n";

    os << "hex:   " << std::hex << std::setfill('0');
    for (int i = 0; i < length; i++) {
        os << std::setw(2) << (int) (uint8_t) data[i] << " ";
    }
    os << "\n";

#ifdef USE_GLOG
    LOG(INFO) << os.str();
#else
    std::cout << os.str() << std::endl;
#endif
}

