//
// Created by Ivik Hostrup.
// Reaction class is used to represent a chemical reaction.
// Baseline to satisfy all requirements.
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
    [[nodiscard]] double GetDelay() const;
    void ComputeDelay(std::mt19937& gen);


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
