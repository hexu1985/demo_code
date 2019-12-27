#include <iostream>

#include <gflags/gflags.h>

/**
 *  定义命令行参数变量
 *  默认的主机地址为 127.0.0.1，变量解释为 'the server host'
 *  默认的端口为 12306，变量解释为 'the server port'
 */
DEFINE_string(host, "127.0.0.1", "the server host");
DEFINE_int32(port, 12306, "the server port");

int main(int argc, char** argv) {
    // 解析命令行参数，一般都放在 main 函数中开始位置
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    // 访问参数变量，加上 FLAGS_
    std::cout << "The server host is: " << FLAGS_host
        << ", the server port is: " << FLAGS_port << std::endl;
    return 0;
}

