#include "AmericanPutOption.h"
#include <algorithm>

// Constructeur de notre classe AmericanPutOptio
AmericanPutOption::AmericanPutOption(double expiry, double strike)
    : AmericanOption(expiry), _strike(strike) {}

// Implémentation de la méthode payoff pour un put d une option americaine
double AmericanPutOption::payoff(double spotPrice) const {
    return std::max(_strike - spotPrice, 0.0);
}

// Implémentation de la methode GetOptionType, dans ce cas c est un put
optionType AmericanPutOption::GetOptionType() const {
    return optionType::Put;
}
