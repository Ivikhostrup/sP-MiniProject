//
// Created by Ivik Hostrup on 6/3/2023.
//
#include <benchmark/benchmark.h>
#include "../src/SimulationMethods.h"

static void BM_multithreadedCovid(benchmark::State& state) {
    for (auto _ : state) {
        MultithreadedCovid(state.range(0));
    }
}

BENCHMARK(BM_multithreadedCovid)->Arg(std::thread::hardware_concurrency());
BENCHMARK(BM_multithreadedCovid)->Arg(1);
BENCHMARK(BM_multithreadedCovid)->Arg(5);
BENCHMARK(BM_multithreadedCovid)->Arg(10);
BENCHMARK(BM_multithreadedCovid)->Arg(20);
