//
// Created by Ivik Hostrup on 6/1/2023.
//

#include "../reactions/ChemicalSystem.h"

#ifndef STOCHASTICSIMULATION_MONITORCALLBACK_H
#define STOCHASTICSIMULATION_MONITORCALLBACK_H

#endif //STOCHASTICSIMULATION_MONITORCALLBACK_H

struct MonitorCallBack {
    virtual void operator()(double time, const ChemicalSystem& chemicalSystem) = 0;
};