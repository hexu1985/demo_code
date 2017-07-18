
#include <iostream>
#include <string>
#include "base64.h"

int main()
{
    char buf[] = {'\0', '\1', '\2', '\3', '\4', '\5', '\6', '\7', '\10', '\11', '\12'};
    std::string orginal(buf, sizeof(buf));

    std::string encode = gloox::Base64::encode64(orginal);
    std::cout << "encode: " << encode << std::endl;
    std::string decode = gloox::Base64::decode64(encode);

    if (decode == orginal) {
        std::cout << "SUCCEED!" << std::endl;
    } else {
        std::cout << "ERROR!" << std::endl;
    }

    return 0;
}

