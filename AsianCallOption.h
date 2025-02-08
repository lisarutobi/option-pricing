#pragma once
#include "AsianOption.h"

// D�finition des options call asiatiques
class AsianCallOption : public AsianOption {
private:
    double _strike; // Prix d'exercice

public:
    // Constructeur
    AsianCallOption(const std::vector<double>& fixing_dates, double strike);

    // Impl�mentation des m�thodes virtuelles pures
    double payoff(double spotPrice) const override; // Payoff pour un call asiatique
    optionType GetOptionType() const override;     // Type de l'option
};
