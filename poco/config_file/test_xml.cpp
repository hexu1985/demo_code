#include "Poco/AutoPtr.h"
#include "Poco/Util/XMLConfiguration.h"
#include <iostream>
 
using namespace std;
using Poco::AutoPtr;
using Poco::Util::XMLConfiguration;
 
int main(int argc, char** argv)
{
    AutoPtr<XMLConfiguration> pConfig(new XMLConfiguration("test.xml"));
    std::string prop1 = pConfig->getString("prop1");
    cout << prop1 << endl;
 
    int prop2 = pConfig->getInt("prop2");
    cout << prop2 << endl;
 
    std::string prop3 = pConfig->getString("prop3");
    cout << prop3 << endl;
 
    std::string prop4 = pConfig->getString("prop3.prop4");
    cout << prop4 << endl;
    prop4 = pConfig->getString("prop3.prop4[@attr]");
    cout << prop4 << endl;
    prop4 = pConfig->getString("prop3.prop4[1][@attr]");
    cout << prop4 << endl;
 
    return 0;
}
