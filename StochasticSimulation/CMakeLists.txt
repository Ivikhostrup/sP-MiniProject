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

include_directories(include)

# Create a library from source files
add_library(stochasticsimulation_lib src/Species.cpp src/Reaction.cpp src/ChemicalSystem.cpp src/CombinedElements.cpp src/Monitor.cpp src/SpeciesQuantityMonitorCallBack.cpp src/CircadianSimulator.cpp src/CsvWriter.cpp src/SimpleSimulator.cpp src/CovidSimulator.cpp src/plot.cpp)

# Link the library to the required Qt5 components
if(Qt5_FOUND)
    target_link_libraries(stochasticsimulation_lib Qt5::Widgets Qt5::Charts)
endif(Qt5_FOUND)

add_executable(StochasticSimulation src/main.cpp)

target_link_libraries(StochasticSimulation stochasticsimulation_lib)

add_subdirectory(tests)

