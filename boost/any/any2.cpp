#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/assert.hpp>
#include <boost/format.hpp>

#define PRINT(xxx) ( std::cout << boost::format("%-20s = ") % (#xxx) << (xxx) << std::endl)


//检测一个any是否能转换成某种类型，RTTI
template<typename T>
bool can_cast_to(const boost::any& a){
    return a.type() == typeid(T);
}

//获取any内部对象的引用，可以用来修改对象的值
template<typename T>
T& get_ref(boost::any& a){
    BOOST_ASSERT_MSG(can_cast_to<T>(a), "any类型转换错误！！！");
    return boost::any_cast<T&>(a);
}

//获取原对象的指针
template<typename T>
T* get_ptr(boost::any& a){
    BOOST_ASSERT_MSG(can_cast_to<T>(a), "any类型转换错误！！！");
    return boost::any_cast<T>(&a);
}



int main(int argc, char const *argv[])
{

/* 1.基本用法 */
    puts("1.基本用法");
    boost::any a(1);
    //获取原对象   
    PRINT(boost::any_cast<int>(a));
    
    //修改原对象的值,改为左值引用即可
    boost::any_cast<int&>(a) = 100;
    PRINT(boost::any_cast<int>(a));

    //获取原对象的指针
    int* ss = boost::any_cast<int>(&a);
    PRINT(*ss);

    //获取原对象的类型信息
    PRINT(a.type().name());
    //检测any中是否保存了对象
    std::cout << std::boolalpha;
    PRINT(a.empty());
    puts("");
/**************************************************************************/
/*二，智能指针。 不能用any保存堆上的原始的指针，会造成内存泄露,应使用智能指针*/

    puts("二，智能指针");
    //下面这样做会造成内存泄露
    int* p = new int(2);
    boost::any ptr_any(p);
    int* tmp = boost::any_cast<int*>(ptr_any);
    PRINT(*tmp);

    //应当使用智能指针，而且只能使用shared_ptr,因为scoped_ptr不能被复制
    //这样在any析构时，会调用shared_ptr的析构函数，释放其持有的资源
    boost::any shared_any(boost::shared_ptr<int>(new int(3) ) );
    auto p_shared = boost::any_cast<boost::shared_ptr<int> >(shared_any);
    PRINT(*p_shared);
    puts("");
/**************************************************************************/
//三，辅助函数：
    puts("三，辅助函数");
    std::string str("hello");
    boost::any xxx(str);

    //检测一个any是否能转换成某种类型，RTTI
    PRINT(can_cast_to<int>(xxx) );
    PRINT(can_cast_to<std::string>(xxx) );

    //获取any内部对象的引用，可以用来修改对象的值
    get_ref<std::string>(xxx) = "world";

    //获取原对象的指针
    PRINT(get_ptr<std::string>(xxx)->size());
    puts("");
/**************************************************************************/
//四，用于容器:
    puts("四，用于容器");
    std::vector<boost::any> vec {
        1,
        std::string("你好！"),
        1.414,    
        boost::shared_ptr<std::string>(new std::string("end") )    
    };
    PRINT(boost::any_cast<int>(vec[0]) );
    PRINT(boost::any_cast<std::string&>(vec[1]) );
    PRINT(boost::any_cast<double>(vec[2]) );
    PRINT(*boost::any_cast<boost::shared_ptr<std::string>>(vec[3]) );

    return 0;
}
