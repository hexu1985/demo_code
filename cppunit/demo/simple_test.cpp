#include <cppunit/TestCase.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TextOutputter.h>

// 定义测试用例
class SimpleTest : public CppUnit::TestCase
{
public:
    void runTest() // 重载测试方法
    {
        int i = 1;
        CPPUNIT_ASSERT_EQUAL(0, i);
    }
};

int main(int argc, char* argv[])
{
    CppUnit::TestResult r; 
    CppUnit::TestResultCollector rc;
    r.addListener(&rc); // 准备好结果收集器 

    SimpleTest t;
    t.run(&r); // 运行测试用例

    CppUnit::TextOutputter o(&rc, std::cout);
    o.write(); // 将结果输出

    return 0;
}
