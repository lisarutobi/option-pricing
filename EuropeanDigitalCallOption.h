#pragma once

#include "EuropeanDigitalOption.h"

class EuropeanDigitalCallOption : public EuropeanDigitalOption {
public:
    EuropeanDigitalCallOption(double expiry, double strike);

   
    optionType GetOptionType() const override;
    double getExpiry() const override;
    double payoff(double spotPrice) const override;
};
