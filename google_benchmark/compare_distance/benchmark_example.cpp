#include <benchmark/benchmark.h>

#include <cmath>

double gx1 = 100;
double gy1 = 100;
double gx2 = 200;
double gy2 = 200;
double dist = 50;
double dist_square = 2500;
volatile bool res = false;


static void compare_distance_square(benchmark::State& state)

{
    for (auto _: state) {
        res = ((gx2-gx1)*(gx2-gx1) + (gy2-gy1)*(gy2-gy1) - dist_square) > 0;
    }

}

BENCHMARK(compare_distance_square);


static void compare_distance(benchmark::State& state)

{

    for (auto _: state) {
        res = (sqrt((gx2-gx1)*(gx2-gx1) + (gy2-gy1)*(gy2-gy1)) - dist) > 0;
    }

}

BENCHMARK(compare_distance);

BENCHMARK_MAIN();
