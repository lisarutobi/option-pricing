#include "BlackScholesPricer.h"
#include "EuropeanDigitalCallOption.h"
#include "EuropeanDigitalPutOption.h"
#include "EuropeanVanillaOption.h"
#include <cmath>
#include <stdexcept>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Implémentation de notre constructeur
BlackScholesPricer::BlackScholesPricer(Option* option, double asset_price, double interest_rate, double volatility)
    : _option(option), _asset_price(asset_price), _interest_rate(interest_rate), _volatility(volatility) {}

// PDF de la distribution normale
double BlackScholesPricer::normalPDF(double x) const {
    return (1.0 / std::sqrt(2.0 * M_PI)) * std::exp(-0.5 * x * x);
}

// CDF de la distribution normale
double BlackScholesPricer::normalCDF(double x) const {
    return 0.5 * std::erfc(-x / std::sqrt(2.0));
}

// Calcul du prix de l'option
double BlackScholesPricer::operator()() const {
    double expiry = _option->getExpiry();  // Maturité
    double strike;

    // Récupération du strike selon le type d'option Vanille ou Digital
    if (auto* digitalCall = dynamic_cast<EuropeanDigitalCallOption*>(_option)) {
        strike = digitalCall->getStrike();
    }
    else if (auto* digitalPut = dynamic_cast<EuropeanDigitalPutOption*>(_option)) {
        strike = digitalPut->getStrike();
    }
    else if (auto* vanillaOption = dynamic_cast<EuropeanVanillaOption*>(_option)) {
        strike = vanillaOption->getStrike();
    }
    else {
        throw std::invalid_argument("Unsupported option type in BlackScholesPricer");
    }

    // Calcul des termes d1 et d2 afin d'utiliser Black Scholes
    double d1 = (std::log(_asset_price / strike) + (_interest_rate + 0.5 * _volatility * _volatility) * expiry) /
        (_volatility * std::sqrt(expiry));
    double d2 = d1 - _volatility * std::sqrt(expiry);

    // Options digitales
    if (dynamic_cast<EuropeanDigitalCallOption*>(_option)) {
        return std::exp(-_interest_rate * expiry) * normalCDF(d2);
    }
    else if (dynamic_cast<EuropeanDigitalPutOption*>(_option)) {
        return std::exp(-_interest_rate * expiry) * normalCDF(-d2);
    }
    // Options vanilles
    else if (dynamic_cast<EuropeanVanillaOption*>(_option) && _option->GetOptionType() == optionType::Call) {
        return _asset_price * normalCDF(d1) - strike * std::exp(-_interest_rate * expiry) * normalCDF(d2);
    }
    else if (dynamic_cast<EuropeanVanillaOption*>(_option) && _option->GetOptionType() == optionType::Put) {
        return strike * std::exp(-_interest_rate * expiry) * normalCDF(-d2) - _asset_price * normalCDF(-d1);
    }
    else {
        throw std::invalid_argument("Unsupported option type in BlackScholesPricer");
    }
}

// Calcul du delta de notre option
double BlackScholesPricer::delta() const {
    double expiry = _option->getExpiry();
    double strike;

    // Récupération du strike selon le type d'option
    if (auto* digitalCall = dynamic_cast<EuropeanDigitalCallOption*>(_option)) {
        strike = digitalCall->getStrike();
    }
    else if (auto* digitalPut = dynamic_cast<EuropeanDigitalPutOption*>(_option)) {
        strike = digitalPut->getStrike();
    }
    else if (auto* vanillaOption = dynamic_cast<EuropeanVanillaOption*>(_option)) {
        strike = vanillaOption->getStrike();
    }
    else {
        throw std::invalid_argument("Unsupported option type in BlackScholesPricer");
    }

    // Calcul des termes d1 et d2
    double d1 = (std::log(_asset_price / strike) + (_interest_rate + 0.5 * _volatility * _volatility) * expiry) /
        (_volatility * std::sqrt(expiry));
    double d2 = d1 - _volatility * std::sqrt(expiry);

    // Calcul du delta de l option
    if (dynamic_cast<EuropeanDigitalCallOption*>(_option)) {
        return std::exp(-_interest_rate * expiry) * normalPDF(d2) / (_asset_price * _volatility * std::sqrt(expiry));
    }
    else if (dynamic_cast<EuropeanDigitalPutOption*>(_option)) {
        return -std::exp(-_interest_rate * expiry) * normalPDF(-d2) / (_asset_price * _volatility * std::sqrt(expiry));
    }
    else if (dynamic_cast<EuropeanVanillaOption*>(_option) && _option->GetOptionType() == optionType::Call) {
        return normalCDF(d1);
    }
    else if (dynamic_cast<EuropeanVanillaOption*>(_option) && _option->GetOptionType() == optionType::Put) {
        return normalCDF(d1) - 1.0;
    }
    else {
        throw std::invalid_argument("Unsupported option type in BlackScholesPricer");
    }
}
