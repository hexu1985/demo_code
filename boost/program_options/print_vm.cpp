#include <iostream>
#include "print_vm.h"

using namespace std;
using namespace boost::program_options;

void print_vm(options_description &opts, variables_map &vm)
{
    if (vm.empty())
    {
        cout << opts << endl;
        return;
    }

    if (vm.count("help"))
    {
        cout << opts << endl;
    }

    //输出查找文件名，因为它有缺省值，故总存在
    cout << "find opt:" << vm["filename"].as<string>() << endl;

    if (vm.count("dir"))
    {
        cout << "dir opt:";
        for(auto& str:
                vm["dir"].as<vector<string> >())
        {   cout << str << ","; }
        cout << endl;
    }

    if (vm.count("depth"))
    {   cout << "depth opt:" << vm["depth"].as<int>() << endl;}
}

