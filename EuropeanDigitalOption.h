#pragma once

#include "Option.h"

class EuropeanDigitalOption : public Option {
protected:
    double _strike; 

public:
    EuropeanDigitalOption(double expiry, double strike);

    double getStrike() const;

    
    virtual optionType GetOptionType() const = 0;

    
    virtual double payoff(double spotPrice) const = 0;
};
