#include <windows.h>

int main(int argc, char *argv[])
{
    ShellExecuteW(nullptr, L"open", L"https://www.baidu.com", nullptr, nullptr, SW_SHOWNORMAL);
    ShellExecuteW(nullptr, L"open", L"D:", nullptr, nullptr, SW_SHOWNORMAL);
    ShellExecuteW(nullptr, L"open", L"D:\\README.txt", nullptr, nullptr, SW_SHOWNORMAL);
    return 0;
}
