//
// Created by Ivik Hostrup on 5/26/2023.
//

#ifndef STOCHASTICSIMULATION_COMBINEDREACTANTS_H
#define STOCHASTICSIMULATION_COMBINEDREACTANTS_H


#include <list>
#include "Species.h"

class CombinedReactants {
public:
private:

};

CombinedReactants operator+(const Species& l, const Species& r) {
    CombinedReactants combination;

    combination.Add(l);
    combination.Add(r);

    return combination;
}


#endif //STOCHASTICSIMULATION_COMBINEDREACTANTS_H
