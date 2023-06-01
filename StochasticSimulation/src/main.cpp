#include <iostream>
#include "reactions/Species.h"
#include "reactions/CombinedElements.h"
#include "reactions/Reaction.h"
#include "reactions/ChemicalSystem.h"
#include "monitors/SpeciesQuantityMonitorCallBack.h"
#include "simulators/CircadianSimulator.h"
#include "simulators/SimpleSimulator.h"

int main() {

    std::vector<std::string> speciesToMonitor = {"A", "B", "C"};
    SpeciesQuantityMonitorCallBack speciesMonitorCallBack(speciesToMonitor);
    Monitor<SpeciesQuantityMonitorCallBack> monitor(speciesMonitorCallBack);

    SimpleSimulator simulator(2000);
    simulator.RunSimulation(monitor);

    return 0;
}
