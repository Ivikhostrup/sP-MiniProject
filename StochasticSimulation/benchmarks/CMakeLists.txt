cmake_minimum_required(VERSION 3.24)

# Google Benchmark requires at least C++11
set(CMAKE_CXX_STANDARD 11)

# List of files
set(BENCHMARK_FILES
        benchmark_multithreaded_covid.cpp
        )

add_executable(Benchmarks ${BENCHMARK_FILES})

target_link_libraries(Benchmarks benchmark::benchmark_main stochasticsimulation_lib)
