#include <cppunit/TestAssert.h>
#include <cppunit/TestFixture.h>

class MathTest : public CppUnit::TestFixture 
{
protected:
    int m_value1, m_value2;
public:
    MathTest() {}
    void setUp () {
        m_value1 = 2;
        m_value2 = 3;
    }

    void testAdd() {
        int result = m_value1 + m_value2;
        CPPUNIT_ASSERT(result == 5);
    }

    void testSub() {
        int result = m_value1 - m_value2;
        CPPUNIT_ASSERT(result == 0);
    }
};
