cmake_minimum_required(VERSION 3.24)
project(StochasticSimulation)

set(CMAKE_CXX_STANDARD 17)

add_executable(StochasticSimulation src/main.cpp src/Species.cpp src/Species.h src/Reaction.cpp src/Reaction.h src/ChemicalSystem.cpp src/ChemicalSystem.h src/CombinedElements.cpp src/CombinedElements.h src/SymbolTable.h src/Monitor.cpp src/Monitor.h src/SpeciesQuantityMonitorCallBack.cpp src/SpeciesQuantityMonitorCallBack.h src/CircadianSimulator.cpp src/CircadianSimulator.h src/CsvWriter.cpp src/CsvWriter.h src/MonitorCallBack.h src/SimpleSimulator.cpp src/SimpleSimulator.h src/DataRecord.cpp src/DataRecord.h)
