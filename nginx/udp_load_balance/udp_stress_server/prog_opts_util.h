#ifndef __prog_opts_util_h
#define __prog_opts_util_h

#include <boost/program_options.hpp>

boost::program_options::variables_map Parse_command_line(int argc, char *argv[]);
void Print_variables_map(const boost::program_options::variables_map &vm);

#endif

