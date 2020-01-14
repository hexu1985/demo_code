1) glog环境变量
GLOG_logtostderr
　　bool，默认为FALSE，将日志打印到标准错误，而不是日志文件
GLOG_alsologtostderr
　　bool，默认为FALSE，将日志打印到日志文件，同时也打印到标准错误
GLOG_stderrthreshold
　　int，默认为2（ERROR），大于等于这个级别的日志才打印到标准错误，当指定这个参数时，GLOG_alsologtostderr参数将会失效
GLOG_minloglevel
　　int，默认为0（INFO）， 小于这个日志级别的将不会打印
GLOG_log_dir
　　string类型，指定日志输出目录，目录必须存在
GLOG_max_log_size
　　int，指定日志文件最大size，超过会被切割，单位为MB
GLOG_stop_logging_if_full_disk
　　bool，默认为FALSE，当磁盘满了之后不再打印日志
GLOG_v
　　int，默认为0，指定GLOG_v=n时，对vlog(m)，当m<=n时才会打印日志

2)常用的标志有:

logtostderr (bool, default=false)
    写日志到stderr而不是日志文件.
    Note: you can set binary flags to true by specifying1, true, or yes (caseinsensitive).Also, you can set binary flags to false by specifying0, false, or no (again, caseinsensitive).

stderrthreshold (int, default=2, whichis ERROR)
    将某级及以上级别的记录同时发送到stderr和日志文件. 严重等级INFO, WARNING, ERROR, FATAL 分别对应 0, 1, 2, 3.

minloglevel (int, default=0, whichis INFO)
    只记录某级及以上级别的记录.

log_dir (string, default="")
    指定日志保存的目录.

v (int, default=0)
    Show all VLOG(m) messages for m less orequal the value of this flag. Overridable by --vmodule.See the section about verbose logging for moredetail.

vmodule (string, default="")
    Per-module verbose level. The argument has to contain acomma-separated list of =.is a glob pattern (e.g., gfs* for all modules whose namestarts with "gfs"), matched against the filename base(that is, name ignoring .cc/.h./-inl.h). overrides any value given by --v.See also the section about verbose logging.
    还有一些其它的标志,自己去logging.cc里面搜索"DEFINE_",爷就不多说了.

    你也可以在程序里修改FLAGS_* 开头的全局变量. 通常设置FLAGS_*开头的变量会立即生效,和日志文件名或路径相关的变量例外.例如FLAGS_log_dir就不能放在google::InitGoogleLogging后面

3) 日志等级
    系统预定义等级：INFO(=0)<WARNING(=1)<ERROR(=2)<FATAL(=3)
    最严重级别是FATAL级别，对应DEBUG模式是DFATAL级别
        在输出FATAL日志消息后，会终止程序运行
        DEBUG模式中，DFATAL级别对应ERROR--便于调试，而非DEBUG模式则对应FATAL
    每个级别都对应有相应的日志文件，日志文件的位置及名称定义如下：
        文件默认存放在临时文件中，windows下是"C:\Users\user_name\AppData\Local\Temp",Linux是"/tmp"
        文件名称：programname.hostname.user_name.log.severity_level.date.time.pid
        Linux系还会创建为每个文件创建一个文件链接
    日志输出采用如下规则：
        每个级别的日志除了输出到对应日志文件中，还输出到每个低级别日志文件中
        如一个ERROR日志，会输出到INFO，WARNING，ERROR三个日志文件中
        默认，ERROR和FATAL消息除了输出到日志文件中之外，还会输出到标准错误中

4) 符号变量
    通过符号变量可以定制日志行为
    设置符号变量的三个方法：
        系统装有google-fglags库，在安装google-glog时会自动使用google-fglags库
            可通过命令行参数来设置符号变量，如--logtostderr=1
            PS:网上查找资料时看到内容：使用google-fglags库后vglgrind会提示内存泄漏(未验证)
        系统未安装google-fglags库，通过使用前缀"GLOG_"的环境变量可设置符号变量
        在程序中，通过修改全局变量(使用前缀"FLAGS_")来设置符号变量
            大多数符号变量修改后会立即生效
            与输出位置有关(如FLAGS_log_dir)，如果要生效需要在google::InitGoogleLogging()之前设置
    符号变量包括：
        logtostderr(bool,default=false),只输出到STDERR而不写入日志文件
        stderrthreshold(int,default=2,which is ERROR)，高于该级别的日志除写入日志文件还输出到STDERR
        minloglevel(int,default=0,which is INFO)，低于该级别的日志消息不输出
        log_dir(string,default="")，日志输出目录
        v(int,default=0)，小于等于该值的VLOG(m)会被输出，否则不会输出
        vmodule(string,default="")，可为源文件定制VLOG日志输出级别
        max_log_size(int,default=1800)，日志文件最大值(单位MB)
        log_link(string,default="")，日志文件的连接所在的文件夹
        stop_logging_if_full_disk(bool,default=false)，如果磁盘写满是否停止记录日志
        alsologtoemail(string,default="")，是否将日志额外发送邮件到指定地址
        logemaillevel(int,default=999)，设置发送邮件的日志等级
        logmailer(string,default="/bin/mail")，发送邮件程序
