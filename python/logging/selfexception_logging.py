# 导入trackback模块
import traceback
import logging

class SelfException(Exception): pass
def main():
    firstMethod()
def firstMethod():
    secondMethod()
def secondMethod():
    thirdMethod()
def thirdMethod():
    raise SelfException("自定义异常信息")
try:
    logging.basicConfig(level=logging.INFO)
    main()
except:
    s = traceback.format_exc()
    # 使用 logging + traceback 模块输出异常
    logging.info(u"使用 traceback 输出异常: {}".format(s))
    # 使用 logging 自定义参数输出异常
    logging.error(u"使用 logging error 参数 exc_info=True 输出异常", exc_info=True)
