#pragma once
#include "Option.h"
#include "MT.h"
#include <vector>

class BlackScholesMCPricer {
// Arguments permettant d'obtenir le prix de l'option à l'aide de la méthode de Mont Carlo 
private:
    Option* _option;           // Pointeur vers l'option
    double _initialPrice;      // Prix initial de l'actif
    double _interestRate;      // Taux sans risque
    double _volatility;        // Volatilité
    int _nbPathsGenerated;     // Nombre de chemins générés
    double _currentEstimate;   // Estimation actuelle du prix
    double _sumOfSquares;      // Somme des carrés des payoffs

public:
    // Constructeur de notre classe 
    BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility);

    // Implémentation des méthodes de notre classe

    // Getter pour obtenir le nombre de chemins générés
    int getNbPaths() const;

    // Génére des chemins Monte Carlo
    void generate(int nb_paths);

    // Retourner l'estimation actuelle du prix de l'option
    double operator()() const;

    // Calculer l'intervalle de confiance à 95 % 
    std::vector<double> confidenceInterval() const;
};
