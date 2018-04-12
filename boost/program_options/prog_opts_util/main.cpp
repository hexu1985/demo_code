#include <vector>
#include <thread>
#include <chrono>
#include <iostream>
#include <atomic>
#include <stdint.h>
#include "prog_opts_util.h"

using namespace std;

int main(int argc, char *argv[])
{
    auto vm = Parse_command_line(argc, argv);
    cout << "program_options: \n";
    Print_variables_map(vm);
    cout << "\n\n" << endl;

    return 0;
}

