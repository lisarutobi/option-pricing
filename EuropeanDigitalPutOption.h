#pragma once

#include "EuropeanDigitalOption.h"

class EuropeanDigitalPutOption : public EuropeanDigitalOption {
public:
    EuropeanDigitalPutOption(double expiry, double strike);

    // Implémentations des méthodes virtuelles
    optionType GetOptionType() const override;
    double getExpiry() const override;
    double payoff(double spotPrice) const override;
};
