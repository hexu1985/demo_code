#include "test.h"

namespace com {

	/**
	 * Created by Jack Tony on 2015/4/3.
	 * @brief 子类
	 */
	class SubClass: public TestClass {

		public: 

			/**
			 * 
			 * <pre><b>copyright: kale</b></pre>
			 * <pre><b>email: </b>developer_kale@qq.com</pre>
			 * <pre><b>company: </b>http://www.cnblogs.com/tianzhijiexian/</pre>
			 * <pre><b>All rights reserved.</b></pre>
			 * @see 参考项 http://www.cnblogs.com/tianzhijiexian/
			 * @brief 方法的简单说明
			 * @author 作者的信息
			 * @date 2011/8/24 8:37:56
			 * @version 0.1
			 * @retval c 描述返回值的类型
			 * @note 注解，可以是详细的注解
			 * @remarks   备注事项（remaks）
			 * @attention 注意事项(attention)
			 * @warning 警告信息
			 * @param a 参数a的说明
			 * @param b 参数b的说明
			 * @return 本函数返回执行结果
			 * 
			 * @throws Exception
			 */
			String subFunction(int a, String b)  throws Exception{
				return "hello world";
			}
	}

}	// namespace com 

