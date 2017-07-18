#ifndef __statistics_h
#define __statistics_h

#include <stdint.h>
#include <chrono>

struct Statistics {
    uint32_t total_send_packets;
    uint64_t total_send_bytes;
    uint32_t total_recv_packets;
    uint64_t total_recv_bytes;
    std::chrono::steady_clock::time_point time_point;
};

void print_statistics(const Statistics &begin, const Statistics &end);

#endif
