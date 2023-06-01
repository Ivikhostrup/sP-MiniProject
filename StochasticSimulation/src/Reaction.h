//
// Created by Ivik Hostrup on 5/26/2023.
//

#ifndef STOCHASTICSIMULATION_REACTION_H
#define STOCHASTICSIMULATION_REACTION_H



#include <memory>
#include <vector>
#include "Species.h"
#include "CombinedElements.h"
#include <iostream>
#include <random>

class Reaction {
public:
    void AddReactant(const std::shared_ptr<Species>& species);
    void AddProduct(const std::shared_ptr<Species>& species);
    void SetRateConstant(const double& rate_constant);
    [[nodiscard]] double GetLambda() const;
    void set_delay(const double& delay);
    [[nodiscard]] double get_delay() const;
    void ComputeDelay(std::default_random_engine& gen);


    [[nodiscard]] const CombinedElements& get_reactants() const;
    [[nodiscard]] const CombinedElements& get_products() const;

    std::string to_string() const;
    friend std::ostream& operator<<(std::ostream& os, const Reaction& reaction);
private:
    CombinedElements m_reactants;
    CombinedElements m_products;
    double m_lambda;
    double m_delay = std::numeric_limits<double>::max();
    void print_reaction(std::ostream& os) const;
};

Reaction operator>>=(const CombinedElements& combinedReactants, const std::shared_ptr<Species>& product);
Reaction operator>>=(const std::shared_ptr<Species>& reactant, const CombinedElements& combinedProducts);
Reaction operator>>=(const CombinedElements& combinedReactants, const CombinedElements& combinedProducts);
Reaction operator>>=(const std::shared_ptr<Species>& reactant, const std::shared_ptr<Species>& product);

#endif //STOCHASTICSIMULATION_REACTION_H
