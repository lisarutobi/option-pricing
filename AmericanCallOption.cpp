#include "AmericanCallOption.h"
#include <algorithm>

// Constructeur de la classe AmericanCallOption
AmericanCallOption::AmericanCallOption(double expiry, double strike)
    : AmericanOption(expiry), _strike(strike) {}

// Impl�mentation de la methode payoff de notre classe AmericanCallOption
double AmericanCallOption::payoff(double spotPrice) const {
    return std::max(spotPrice - _strike, 0.0);
}

// Impl�mentation de GetOptionType qui est dans notre classe AmericanCallOption un call
optionType AmericanCallOption::GetOptionType() const {
    return optionType::Call;
}