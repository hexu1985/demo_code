#!-*-encoding:utf-8-*-

"""

测试多级调用异常捕获
"""


import logging
import traceback

# 在这里设置记录的是什么等级以上的日志
#logging.basicConfig(filename='run.log', format='%(asctime)s - %(name)s - %(levelname)s -%(module)s: %(message)s',
#                    datefmt='%Y-%m-%d %H:%M:%S', level=20)

def foo(s):
    return 10 / int(s)



def bar(s):
    return foo(s) * 2


def main():

    for i in range(10):
        try:
            res = bar('{}'.format(i))
            print("result is: {}".format(res))
            logging.info("运行结果为: {}".format(res))
        except Exception as e:
            s = traceback.format_exc()
            # 使用 logging + traceback 模块输出异常
            logging.info(u"使用 traceback 输出异常: {}".format(s))
            # 使用 logging 自定义参数输出异常
            logging.error(u"使用 logging error 参数 exc_info=True 输出异常", exc_info=True)
            # 也可以直接使用 logging 的 exception 函数输出异常堆栈信息
            logging.exception(u"使用logging exception 函数直接输出异常堆栈 {}".format(e))
            #logging.exception(e)

            print("Error: ", e)


if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    main()
