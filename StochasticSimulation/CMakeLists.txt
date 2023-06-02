cmake_minimum_required(VERSION 3.24)
project(StochasticSimulation)

set(CMAKE_CXX_STANDARD 17)

# Qt5
find_package(Qt5 COMPONENTS Widgets Charts QUIET)
if (Qt5_FOUND)
    message(STATUS "Qt5 found, fantastic!")
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)
else(Qt5_FOUND)
    message(WARNING "Qt5 NOT found, test_qt5 will be disabled. Please install qt5charts development package.")
endif(Qt5_FOUND)

add_executable(StochasticSimulation src/main.cpp src/Species.cpp src/Species.h src/Reaction.cpp src/Reaction.h src/ChemicalSystem.cpp src/ChemicalSystem.h src/CombinedElements.cpp src/CombinedElements.h src/SymbolTable.h src/Monitor.cpp src/Monitor.h src/SpeciesQuantityMonitorCallBack.cpp src/SpeciesQuantityMonitorCallBack.h src/CircadianSimulator.cpp src/CircadianSimulator.h src/CsvWriter.cpp src/CsvWriter.h src/MonitorCallBack.h src/SimpleSimulator.cpp src/SimpleSimulator.h src/CovidSimulator.cpp src/CovidSimulator.h src/plot.hpp src/plot.cpp)

if(Qt5_FOUND)
    target_link_libraries(StochasticSimulation Qt5::Widgets Qt5::Charts)
endif(Qt5_FOUND)