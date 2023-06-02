#include <iostream>
#include "SpeciesQuantityMonitorCallBack.h"
#include "CircadianSimulator.h"
#include "SimpleSimulator.h"
#include "CovidSimulator.h"
#include "plot.hpp"

void PlotSimple(){
    std::vector<std::string> speciesToMonitor = {"A", "B", "C"};
    SpeciesQuantityMonitorCallBack speciesMonitorCallBack(speciesToMonitor);
    Monitor monitor(speciesMonitorCallBack);

    SimpleSimulator simulator(1000);
    simulator.RunFirstSimulation(monitor);
};

void PlotCircadian(){
    std::vector<std::string> speciesToMonitor = {"C", "A", "R"};
    SpeciesQuantityMonitorCallBack speciesMonitorCallBack(speciesToMonitor);
    Monitor monitor(speciesMonitorCallBack);

    CircadianSimulator simulator(100, 24);
    simulator.RunSimulation(monitor);
};

void plotCovid(){
    std::vector<std::string> speciesToMonitor = {"S", "E", "I","H","R"};
    SpeciesQuantityMonitorCallBack speciesMonitorCallBack(speciesToMonitor);
    Monitor monitor(speciesMonitorCallBack);


    CovidSimulator simulator(10000, 100);
    simulator.RunCovidSimulator(monitor);
}

int main() {



    return 0;
}
