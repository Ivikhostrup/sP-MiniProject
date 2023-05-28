#include <iostream>
#include "Species.h"
#include "CombinedElements.h"
#include "Reaction.h"
#include "System.h"

int main() {
    System system;

    auto A = system.AddSpecies("A", 100);
    auto B = system.AddSpecies("B", 0);
    auto C = system.AddSpecies("C", 1);

    const double lambda = 0.001;

    system.AddReaction(A + B >>= B + C, lambda);

    system.Simulate(100);


    return 0;
}
