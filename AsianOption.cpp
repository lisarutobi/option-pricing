#include "AsianOption.h"
#include <numeric> // Pour std::accumulate

// Constructeur
AsianOption::AsianOption(const std::vector<double>& fixing_dates)
    : Option(fixing_dates.empty() ? throw std::invalid_argument("Fixing dates cannot be empty.") : fixing_dates.back()),
    _fixingDates(fixing_dates) {}

// IMPLEMENTATION DES METHODES DE NOTRE CLASSE ASIANOPTION

// Getter pour les timestamps
const std::vector<double>& AsianOption::getFixingDates() const {
    return _fixingDates;
}

// Implémentation de getExpiry
double AsianOption::getExpiry() const {
    return Option::getExpiry();
}

// Implémentation de isAsianOption
bool AsianOption::isAsianOption() const {
    return true; // Indique que c'est une option asiatique
}

// Implémentation de payoffPath
double AsianOption::payoffPath(const std::vector<double>& path) const {
    if (path.empty()) {
        throw std::invalid_argument("Path cannot be empty.");
    }

    // Calculer la moyenne des prix
    double averagePrice = std::accumulate(path.begin(), path.end(), 0.0) / path.size();

    // Appliquer le payoff sur la moyenne
    return payoff(averagePrice);
}
