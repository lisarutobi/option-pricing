#include "AsianCallOption.h"
#include <algorithm> // Pour std::max

// Constructeur
AsianCallOption::AsianCallOption(const std::vector<double>& fixing_dates, double strike)
    : AsianOption(fixing_dates), _strike(strike) {}

// Implémentation du payoff
double AsianCallOption::payoff(double spotPrice) const {
    return std::max(spotPrice - _strike, 0.0);
}

// Type de l'option
optionType AsianCallOption::GetOptionType() const {
    return optionType::Call;
}
