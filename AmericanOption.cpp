#include "AmericanOption.h"

// Constructeur de notre classe AmericanOption
AmericanOption::AmericanOption(double expiry) : Option(expiry) {}

// Implémentation de isAmericanOption
bool AmericanOption::isAmericanOption() const {
    return true;
}
