#include "EuropeanDigitalPutOption.h"

// Constructeur
EuropeanDigitalPutOption::EuropeanDigitalPutOption(double expiry, double strike)
    : EuropeanDigitalOption(expiry, strike) {}

// Type d'option (Put)
optionType EuropeanDigitalPutOption::GetOptionType() const {
    return optionType::Put;
}

// Retourne la maturité
double EuropeanDigitalPutOption::getExpiry() const {
    return Option::getExpiry();
}

// Payoff pour Put Digital
double EuropeanDigitalPutOption::payoff(double spotPrice) const {
    return spotPrice <= _strike ? 1.0 : 0.0; // Payoff = 1 si spotPrice <= strike
}
