//
// Created by Ivik Hostrup on 5/29/2023.
//

#ifndef STOCHASTICSIMULATION_MONITOR_H
#define STOCHASTICSIMULATION_MONITOR_H


#include <utility>

//forward declaration
class ChemicalSystem;

template<typename CallBackType>
class Monitor {
public:
    explicit Monitor(CallBackType& callback) : m_callback(callback) {}

    void OnStateChange(double time, const ChemicalSystem& chemicalSystem) {
        m_callback(time, chemicalSystem);
    }

    CallBackType& GetCallback() {
        return m_callback;
    }
private:
    CallBackType& m_callback;
};


#endif //STOCHASTICSIMULATION_MONITOR_H
