#include "CRRPricer.h"
#include <cmath>
#include <stdexcept>

// Constructeurs de notre classe CRRPricer

CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate)
    : _option(option), _depth(depth), _S0(asset_price), _U(up), _D(down), _R(interest_rate), _computed(false) {
    if (!option) {
        throw std::invalid_argument("Option pointer cannot be null.");
    }
    if (depth < 1) {
        throw std::invalid_argument("Depth must be at least 1.");
    }
    if (_D >= _R || _R >= _U) {
        throw std::invalid_argument("Arbitrage condition violated: D < R < U.");
    }

    _q = (_R - _D) / (_U - _D);
    _priceTree.setDepth(depth + 1);
    _valueTree.setDepth(depth + 1);
    _exerciseTree.setDepth(depth + 1);
}

CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double interest_rate, double volatility)
    : _option(option), _depth(depth), _S0(asset_price) {
    double h = option->getExpiry() / depth;
    _U = std::exp((interest_rate + 0.5 * volatility * volatility) * h + volatility * std::sqrt(h)) - 1;
    _D = std::exp((interest_rate + 0.5 * volatility * volatility) * h - volatility * std::sqrt(h)) - 1;
    _R = std::exp(interest_rate * h) - 1;
    _q = (_R - _D) / (_U - _D);
    _priceTree.setDepth(depth + 1);
    _valueTree.setDepth(depth + 1);
    _exerciseTree.setDepth(depth + 1);
}

// Implémentation des méthodes de la classe CRRPricer

// Vérification de l'absence d'arbitrage
void CRRPricer::checkArbitrage() {
    if (_D >= _R || _R >= _U) {
        throw std::logic_error("Arbitrage condition violated: D < R < U.");
    }
}

// Construire l'arbre des prix
void CRRPricer::buildPriceTree() {
    _priceTree.setNode(0, 0, _S0);
    for (int n = 1; n <= _depth; ++n) {
        for (int i = 0; i <= n; ++i) {
            double price = _S0 * std::pow(1 + _U, i) * std::pow(1 + _D, n - i);
            _priceTree.setNode(n, i, price);
        }
    }
}

// Construction de l'arbre avec des valeurs et des exercices
void CRRPricer::buildValueTree() {
    // Étape 1 : valeurs à l'expiration
    for (int i = 0; i <= _depth; ++i) {
        double terminalPrice = _priceTree.getNode(_depth, i);
        _valueTree.setNode(_depth, i, _option->payoff(terminalPrice));
        _exerciseTree.setNode(_depth, i, true);
    }

    // Étape 2 : Backward induction
    for (int n = _depth - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            double continuationValue = (_q * _valueTree.getNode(n + 1, i + 1) +
                (1 - _q) * _valueTree.getNode(n + 1, i)) / (1 + _R);
            double intrinsicValue = _option->payoff(_priceTree.getNode(n, i));

            if (_option->isAmericanOption()) {
                double nodeValue = std::max(continuationValue, intrinsicValue);
                _valueTree.setNode(n, i, nodeValue);
                _exerciseTree.setNode(n, i, intrinsicValue >= continuationValue);
            }
            else {
                _valueTree.setNode(n, i, continuationValue);
                _exerciseTree.setNode(n, i, false);
            }
        }
    }
}

// Calcul de la formule fermée (non utilisé ici mais laissé tel quel)
double CRRPricer::computeClosedForm() const {
    double optionValue = 0.0;
    for (int i = 0; i <= _depth; ++i) {
        double priceAtNode = _S0 * std::pow(1 + _U, i) * std::pow(1 + _D, _depth - i);
        double p_up = std::log(_q);
        double p_down = std::log(1 - _q);
        double probability = std::exp(p_up * i + p_down * (_depth - i));
        double payoff = _option->payoff(priceAtNode);
        optionValue += probability * payoff;
    }
    return optionValue / std::pow(1 + _R, _depth);
}

void CRRPricer::compute() {
    if (!_computed) {
        buildPriceTree();
        buildValueTree();
        _computed = true;
    }
}

double CRRPricer::get(int n, int i) const {
    return _valueTree.getNode(n, i);
}

bool CRRPricer::getExercise(int n, int i) const {
    return _exerciseTree.getNode(n, i);
}

double CRRPricer::operator()(bool closed_form) {
    if (closed_form) {
        return computeClosedForm();
    }
    else {
        compute();
        return get(0, 0);
    }
}
