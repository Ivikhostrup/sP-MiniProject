//
// Created by Ivik Hostrup on 5/29/2023.
//

#ifndef STOCHASTICSIMULATION_MONITOR_H
#define STOCHASTICSIMULATION_MONITOR_H


#include "ChemicalSystem.h"

class Monitor {
public:
    virtual void OnStateChange(double time, const ChemicalSystem& chemicalSystem) = 0;
};


#endif //STOCHASTICSIMULATION_MONITOR_H
