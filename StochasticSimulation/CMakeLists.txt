cmake_minimum_required(VERSION 3.24)
project(StochasticSimulation)

set(CMAKE_CXX_STANDARD 17)

add_executable(StochasticSimulation src/main.cpp src/species.cpp src/species.h src/reaction.cpp src/reaction.h src/simulation.cpp src/simulation.h)
