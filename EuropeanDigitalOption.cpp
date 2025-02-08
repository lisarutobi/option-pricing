#include "EuropeanDigitalOption.h"


EuropeanDigitalOption::EuropeanDigitalOption(double expiry, double strike)
    : Option(expiry), _strike(strike) {}

double EuropeanDigitalOption::getStrike() const {
    return _strike;
}
