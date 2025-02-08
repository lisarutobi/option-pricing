#pragma once
#include "AmericanOption.h"

// Implementation des options put Am�ricaines
class AmericanPutOption : public AmericanOption {
private:
    double _strike;

public:
    AmericanPutOption(double expiry, double strike); // constructeur

    // D�finition des m�thodes de la classe 
    double payoff(double spotPrice) const override;
    optionType GetOptionType() const override;
};
