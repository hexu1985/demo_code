#include <iostream>
using namespace std;
 
#include "Poco/Util/Application.h"
#include "Poco/Path.h"
using namespace Poco::Util;
 
#include "Poco/AutoPtr.h"
#include "Poco/Util/IniFileConfiguration.h"
using Poco::AutoPtr;
using Poco::Util::IniFileConfiguration;
 
int main(int argc, char** argv)
{
    AutoPtr<IniFileConfiguration> pConf(new IniFileConfiguration("Test.ini"));
    std::string path = pConf->getString("windows.somePath");
    int svalue = pConf->getInt("windows.someValue");
    std::cout << path << endl;
    cout << svalue << endl;
 
    std::string path1 = pConf->getString("linux.somePath");
    int svalue1 = pConf->getInt("linux.someValue");
    std::cout << path1 << endl;
    cout << svalue1 << endl;
    return 0;
}
