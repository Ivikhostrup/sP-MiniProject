//
// Created by Ivik Hostrup.
// Monitor callback interface
// Part of requirement 7
//

#include "ChemicalSystem.h"

#ifndef STOCHASTICSIMULATION_MONITORCALLBACK_H
#define STOCHASTICSIMULATION_MONITORCALLBACK_H

#endif //STOCHASTICSIMULATION_MONITORCALLBACK_H

struct MonitorCallBack {
    virtual void operator()(double time, const ChemicalSystem& chemicalSystem) = 0;
};