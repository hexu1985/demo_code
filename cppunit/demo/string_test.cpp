#include <cppunit/TestCase.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>

// 定义测试类
class StringTest : public CppUnit::TestFixture
{
public:
    void setUp() // 初始化
    {
        m_str1 = "Hello, world";
        m_str2 = "Hi, cppunit";
    }

    void tearDown() // 清理
    {
    }

    void testSwap() // 测试方法1
    {
        std::string str1 = m_str1;
        std::string str2 = m_str2;
        m_str1.swap(m_str2);
        
        CPPUNIT_ASSERT(m_str1 == str2);
        CPPUNIT_ASSERT(m_str2 == str1);
    }

    void testFind() // 测试方法2
    {
        int pos1 = m_str1.find(',');
        int pos2 = m_str2.rfind(',');

        CPPUNIT_ASSERT_EQUAL(5, pos1);
        CPPUNIT_ASSERT_EQUAL(2, pos2);
    }

protected:
    std::string     m_str1;
    std::string     m_str2;
};

int main(int argc, char* argv[])
{
    CppUnit::TestResult r; 
    CppUnit::TestResultCollector rc;
    r.addListener(&rc); // 准备好结果收集器 

    CppUnit::TestRunner runner; // 定义执行实体
    runner.addTest(new CppUnit::TestCaller<StringTest>("testSwap", &StringTest::testSwap)); // 构建测试用例1
    runner.addTest(new CppUnit::TestCaller<StringTest>("testFind", &StringTest::testFind)); // 构建测试用例2
    runner.run(r); // 运行测试

    CppUnit::TextOutputter o(&rc, std::cout);
    o.write(); // 将结果输出

    return rc.wasSuccessful() ? 0 : -1;
}
