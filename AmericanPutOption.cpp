#include "AmericanPutOption.h"
#include <algorithm>

// Constructeur de notre classe AmericanPutOptio
AmericanPutOption::AmericanPutOption(double expiry, double strike)
    : AmericanOption(expiry), _strike(strike) {}

// Impl�mentation de la m�thode payoff pour un put d une option americaine
double AmericanPutOption::payoff(double spotPrice) const {
    return std::max(_strike - spotPrice, 0.0);
}

// Impl�mentation de la methode GetOptionType, dans ce cas c est un put
optionType AmericanPutOption::GetOptionType() const {
    return optionType::Put;
}
