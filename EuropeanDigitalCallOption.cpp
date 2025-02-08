#include "EuropeanDigitalCallOption.h"

// Constructeur
EuropeanDigitalCallOption::EuropeanDigitalCallOption(double expiry, double strike)
    : EuropeanDigitalOption(expiry, strike) {}

// Type d'option (Call)
optionType EuropeanDigitalCallOption::GetOptionType() const {
    return optionType::Call;
}

// Retourne la maturité
double EuropeanDigitalCallOption::getExpiry() const {
    return Option::getExpiry(); // Appelle la méthode getExpiry() de la classe de base Option
}

// Payoff pour Call Digital
double EuropeanDigitalCallOption::payoff(double spotPrice) const {
    return spotPrice >= _strike ? 1.0 : 0.0; // Payoff = 1 si spotPrice >= strike
}




































