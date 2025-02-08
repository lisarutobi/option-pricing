#pragma once
#include "AsianOption.h"

// Implémentation des options asiatiques de type put
class AsianPutOption : public AsianOption {
private:
    double _strike; 

public:
    // Constructeur
    AsianPutOption(const std::vector<double>& fixing_dates, double strike);

    // Implémentation des méthodes virtuelles pures
    double payoff(double spotPrice) const override; // Payoff pour un put asiatique
    optionType GetOptionType() const override;     // Type de l'option
};
