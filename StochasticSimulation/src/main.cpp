#include <iostream>
#include "Species.h"
#include "CombinedElements.h"
#include "Reaction.h"
#include "ChemicalSystem.h"

int main() {
    ChemicalSystem system;

    auto A = system.AddSpecies("A", 100);
    auto B = system.AddSpecies("B", 0);
    auto C = system.AddSpecies("C", 1);

    const double lambda = 0.001;

    system.AddReaction(A + C >>= B + C, lambda);

    system.Simulate(2000.0);


    return 0;
}
