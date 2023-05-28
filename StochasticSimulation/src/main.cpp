#include <iostream>
#include "Species.h"
#include "CombinedElements.h"
#include "Reaction.h"
#include "System.h"

int main() {
    System system;

    auto DA = system.AddSpecies("DA", 0);
    auto R = system.AddSpecies("R", 0);
    auto D_A = system.AddSpecies("D_A", 0);
    auto DR = system.AddSpecies("DR", 0);

    system.AddReaction(DA + R >>= D_A + DR, 1);

    // print reactions in system
    std::cout << system << std::endl;

    return 0;
}
