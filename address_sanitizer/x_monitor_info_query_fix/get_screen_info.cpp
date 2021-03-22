#include "x_monitor_info_query.hpp"

int main (int argc, char **argv)
{
    for (int i = 0; i < 100; i++) {
        XMonitorInfoQuery query;
        query.print();
    }
  return (0);
}
