#include "BlackScholesMCPricer.h"
#include "AsianOption.h"
#include <cmath>
#include <stdexcept>
#include <numeric>

// Constructeur de notre classe BlackScholesMCPricer
BlackScholesMCPricer::BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility)
    : _option(option),
    _initialPrice(initial_price),
    _interestRate(interest_rate),
    _volatility(volatility),
    _nbPathsGenerated(0),
    _currentEstimate(0.0),
    _sumOfSquares(0.0) {
    if (!option) {
        throw std::invalid_argument("Option pointer cannot be null.");
    }
}

// Implémentations des méthodes de notre classe BlackScholesMCPricer

// Getter pour le nombre de chemins générés
int BlackScholesMCPricer::getNbPaths() const {
    return _nbPathsGenerated;
}

// Génére des chemins Monte Carlo et met à jour l'estimation
void BlackScholesMCPricer::generate(int nb_paths) {
    if (nb_paths <= 0) {
        throw std::invalid_argument("Number of paths must be positive.");
    }

    double T = _option->getExpiry();
    const std::vector<double>& fixingDates = _option->isAsianOption()
        ? dynamic_cast<AsianOption*>(_option)->getFixingDates()
        : std::vector<double>{ T };

    int m = fixingDates.size();
    double discountFactor = std::exp(-_interestRate * T);
    double sumPayoff = 0.0;

    for (int i = 0; i < nb_paths; ++i) {
        std::vector<double> pathPrices(m);

        // Génération du premier prix
        pathPrices[0] = _initialPrice * std::exp(
            (_interestRate - 0.5 * _volatility * _volatility) * fixingDates[0] +
            _volatility * std::sqrt(fixingDates[0]) * MT::rand_norm()
        );

        // Génération des prix restants
        for (int k = 1; k < m; ++k) {
            double dt = fixingDates[k] - fixingDates[k - 1];
            pathPrices[k] = pathPrices[k - 1] * std::exp(
                (_interestRate - 0.5 * _volatility * _volatility) * dt +
                _volatility * std::sqrt(dt) * MT::rand_norm()
            );
        }

        // Calcul du payoff
        double payoff = _option->payoffPath(pathPrices);
        
        sumPayoff += payoff;
        _sumOfSquares += payoff * payoff;
    }

    _nbPathsGenerated += nb_paths;

    // Calcul de l'estimation actuelle
    _currentEstimate = (sumPayoff / _nbPathsGenerated) * discountFactor;
}


// Retourne l'estimation actuelle du prix de l'option
double BlackScholesMCPricer::operator()() const {
    if (_nbPathsGenerated == 0) {
        throw std::runtime_error("Monte Carlo estimate is undefined. Generate paths first.");
    }
    return _currentEstimate;
}

// Calcule l'intervalle de confiance à 95% 
std::vector<double> BlackScholesMCPricer::confidenceInterval() const {
    if (_nbPathsGenerated < 2) {
        throw std::runtime_error("Not enough paths to compute confidence interval.");
    }

    double variance = (_sumOfSquares / _nbPathsGenerated) - (_currentEstimate * _currentEstimate);
    double standardError = std::sqrt(variance / _nbPathsGenerated);

    // Intervalle de confiance : moyenne ± 1.96 * erreur standard
    return { _currentEstimate - 1.96 * standardError, _currentEstimate + 1.96 * standardError };
}
