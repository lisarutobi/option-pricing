#pragma once
#include "Option.h"

class EuropeanVanillaOption : public Option {
private:
    double _strike;
    optionType _type; // Ajout d'un attribut pour g�rer call ou put

public:
    // Ajout d'un param�tre type avec une valeur par d�faut (optionType::Call)
    EuropeanVanillaOption(double expiry, double strike, optionType type = optionType::Call);

    double getStrike() const;
    friend class BlackScholesPricer;
    double getExpiry() const override;
    double payoff(double spotPrice) const override;
    optionType GetOptionType() const override;
};
