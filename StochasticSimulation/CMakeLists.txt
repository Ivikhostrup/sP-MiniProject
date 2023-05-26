cmake_minimum_required(VERSION 3.24)
project(StochasticSimulation)

set(CMAKE_CXX_STANDARD 17)

add_executable(StochasticSimulation src/main.cpp src/Species.cpp src/Species.h src/Reaction.cpp src/Reaction.h src/Simulation.cpp src/Simulation.h src/CombinedReactants.cpp src/CombinedReactants.h src/ReactionSystem.cpp src/ReactionSystem.h)
