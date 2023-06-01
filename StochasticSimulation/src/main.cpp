#include <iostream>
#include "reactions/Species.h"
#include "reactions/CombinedElements.h"
#include "reactions/Reaction.h"
#include "reactions/ChemicalSystem.h"
#include "monitors/SpeciesQuantityMonitorCallBack.h"
#include "simulators/CircadianSimulator.h"

int main() {

    std::vector<std::string> speciesToMonitor = {"A", "R", "C"};
    SpeciesQuantityMonitorCallBack speciesMonitorCallBack(speciesToMonitor);
    Monitor<SpeciesQuantityMonitorCallBack> monitor(speciesMonitorCallBack);

    CircadianSimulator simulator(100, 100);
    simulator.RunSimulation(monitor);

    return 0;
}
