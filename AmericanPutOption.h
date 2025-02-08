#pragma once
#include "AmericanOption.h"

// Implementation des options put Américaines
class AmericanPutOption : public AmericanOption {
private:
    double _strike;

public:
    AmericanPutOption(double expiry, double strike); // constructeur

    // Définition des méthodes de la classe 
    double payoff(double spotPrice) const override;
    optionType GetOptionType() const override;
};
