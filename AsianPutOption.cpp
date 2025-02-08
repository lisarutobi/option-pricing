#include "AsianPutOption.h"
#include <algorithm> // Pour std::max

// Constructeur de la classe AsianPutOption
AsianPutOption::AsianPutOption(const std::vector<double>& fixing_dates, double strike)
    : AsianOption(fixing_dates), _strike(strike) {}

//Implementation des methodes de notre classe AsianPutOption
// Implémentation du payoff
double AsianPutOption::payoff(double spotPrice) const {
    return std::max(_strike - spotPrice, 0.0);
}

optionType AsianPutOption::GetOptionType() const {
    return optionType::Put;
}
