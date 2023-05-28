#include <iostream>
#include "Species.h"
#include "CombinedElements.h"
#include "Reaction.h"
#include "System.h"

int main() {

    auto DA = std::make_shared<Species>("DA", 1);
    auto D_A = std::make_shared<Species>("D_A", 0);
    auto DR = std::make_shared<Species>("DR", 1);
    auto D_R = std::make_shared<Species>("D_R", 0);
    auto MA = std::make_shared<Species>("MA", 0);
    auto MR = std::make_shared<Species>("MR", 0);
    auto A = std::make_shared<Species>("A", 0);
    auto R = std::make_shared<Species>("R", 0);
    auto C = std::make_shared<Species>("C", 0);


    System system;
    system.AddSpecies("A", 0);
    system.AddReaction(DA + R >>= D_A + DR, 1);



    // print reactions in system
    std::cout << system << std::endl;

    return 0;
}
