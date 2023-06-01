cmake_minimum_required(VERSION 3.24)
project(StochasticSimulation)

set(CMAKE_CXX_STANDARD 17)

add_executable(StochasticSimulation src/main.cpp src/reactions/Species.cpp src/reactions/Species.h src/reactions/Reaction.cpp src/reactions/Reaction.h src/reactions/ChemicalSystem.cpp src/reactions/ChemicalSystem.h src/reactions/CombinedElements.cpp src/reactions/CombinedElements.h src/symbolTable/SymbolTable.h src/monitors/Monitor.cpp src/monitors/Monitor.h src/monitors/SpeciesQuantityMonitorCallBack.cpp src/monitors/SpeciesQuantityMonitorCallBack.h src/simulators/CircadianSimulator.cpp src/simulators/CircadianSimulator.h src/reporting/CsvWriter.cpp src/reporting/CsvWriter.h src/monitors/MonitorCallBack.h)
