#include <stdint.h>
#include <stdio.h>
#include <iostream>

#include <gflags/gflags.h>

// 定义对 FLAGS_port 的检查函数
static bool ValidatePort(const char* name, int32_t value) {
    if (value > 0 && value < 32768) {
        return true;
    }
    printf("Invalid value for --%s: %d\n", name, (int)value);
    return false;
}

/**
 *  设置命令行参数变量
 *  默认的主机地址为 127.0.0.1，变量解释为 'the server host'
 *  默认的端口为 12306，变量解释为 'the server port'
 */
DEFINE_string(host, "127.0.0.1", "the server host");
DEFINE_int32(port, 12306, "the server port");

// 使用全局 static 变量来注册函数，static 变量会在 main 函数开始时就调用
static const bool port_dummy = gflags::RegisterFlagValidator(&FLAGS_port, &ValidatePort);

int main(int argc, char** argv) {
    // 解析命令行参数，一般都放在 main 函数中开始位置
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    std::cout << "The server host is: " << FLAGS_host
        << ", the server port is: " << FLAGS_port << std::endl;

    // 使用 SetCommandLineOption 函数对参数进行设置才会调用检查函数
    gflags::SetCommandLineOption("port", "-2");
    std::cout << "The server host is: " << FLAGS_host
        << ", the server port is: " << FLAGS_port << std::endl;
    return 0;
}
