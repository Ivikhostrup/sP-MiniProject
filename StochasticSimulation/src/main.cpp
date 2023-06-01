#include <iostream>
#include "Species.h"
#include "CombinedElements.h"
#include "Reaction.h"
#include "ChemicalSystem.h"
#include "SpeciesQuantityMonitorCallBack.h"
#include "CircadianSimulator.h"
#include "SimpleSimulator.h"

int main() {

    std::vector<std::string> speciesToMonitor = {"A", "B", "C"};
    SpeciesQuantityMonitorCallBack speciesMonitorCallBack(speciesToMonitor);
    Monitor<SpeciesQuantityMonitorCallBack> monitor(speciesMonitorCallBack);


    SimpleSimulator simulator(100000);
    simulator.RunFirstSimulation(monitor);

    return 0;
}
