#include "DemoTest.h"
#include <iostream>
#include <cppunit/extensions/HelperMacros.h>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(DemoTest);

void DemoTest::setUp()
{
    cout << "DemoTest::setUp()" << endl;
}

void DemoTest::tearDown()
{
    cout << "DemoTest::tearDown()" << endl;
}

void DemoTest::testFunc()
{
    cout << "DemoTest::testFunc()" << endl;
    CPPUNIT_ASSERT(12 == 11+1);
}
