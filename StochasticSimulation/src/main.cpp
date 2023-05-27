#include <iostream>
#include "Species.h"
#include "CombinedElements.h"
#include "Reaction.h"
#include "System.h"

int main() {

    auto A = std::make_shared<Species>("A", 1);
    auto B = std::make_shared<Species>("B", 1);
    auto C = std::make_shared<Species>("C", 1);
    auto D = std::make_shared<Species>("D", 1);

    CombinedElements combinedAB = A + B;
    CombinedElements combinedCD = C + D;
    auto reaction = std::make_shared<Reaction>(combinedAB >>= combinedCD);

    // Declare new system object
    System system;

    // Add reaction to system
    system.AddReaction(reaction, 1);

    // print reaction
    std::cout << *reaction << std::endl;
    return 0;
}
