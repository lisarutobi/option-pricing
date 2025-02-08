#pragma once
#include "AmericanOption.h"

class AmericanCallOption : public AmericanOption {
// La classe AmericanCallOption est la classe fille d'AmericanOption, il prend en compte un nouvel argument 
private:
    double _strike;

public:
    // Definition du constructeur de la classe
    AmericanCallOption(double expiry, double strike);
    // Definition des différentes méthodes de la classe
    double payoff(double spotPrice) const override;
    optionType GetOptionType() const override;
};
