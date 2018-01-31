#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include "MathTest.h"

int main(int argc, char **argv)
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestSuite *suite = new CppUnit::TestSuite();

    suite->addTest(new CppUnit::TestCaller<MathTest>\
            ("testAdd", &MathTest::testAdd));

    suite->addTest(new CppUnit::TestCaller<MathTest>\
            ("testSub", &MathTest::testSub));

    runner.addTest(suite);

    runner.run("", true);
    return 0;
}
