#include "EuropeanVanillaOption.h"
#include <iostream>
#include <algorithm>

EuropeanVanillaOption::EuropeanVanillaOption(double expiry, double strike, optionType type)
    : Option(expiry), _strike(strike), _type(type)
{
    if (expiry < 0 || strike < 0) {
        std::cerr << "Attention, expiry et strike doivent etre positifs" << std::endl;
        if (expiry < 0) expiry = -expiry;
        if (strike < 0) strike = -strike;
    }
}

double EuropeanVanillaOption::getStrike() const {
    return _strike;
}

double EuropeanVanillaOption::getExpiry() const {
    return Option::getExpiry();
}

double EuropeanVanillaOption::payoff(double spotPrice) const {
    if (_type == optionType::Call) {
        return std::max(spotPrice - _strike, 0.0);
    }
    else {
        // Dans le cas d'un put
        return std::max(_strike - spotPrice, 0.0);
    }
}

optionType EuropeanVanillaOption::GetOptionType() const {
    return _type;
}
