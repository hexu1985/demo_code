#include "Poco/AutoPtr.h"
#include <iostream>
#include "Poco/Util/PropertyFileConfiguration.h"
 
using Poco::AutoPtr;
using Poco::Util::PropertyFileConfiguration;
using namespace std;
using namespace Poco::Util;
 
int main(int argc, char** argv)
{
    AutoPtr<PropertyFileConfiguration> pConf;
    pConf = new PropertyFileConfiguration("test.properties");
    std::string key1 = pConf->getString("key1");
    int value1 = pConf->getInt("key2");
    std::string logV = pConf->getString("key3.longValue");
    std::string path = pConf->getString("path");
    std::cout << key1 << endl;
    cout << value1 << endl;
    cout << logV << endl;
    cout << path << endl;
    return 0;
}
