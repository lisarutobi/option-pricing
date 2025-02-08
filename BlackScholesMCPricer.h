#pragma once
#include "Option.h"
#include "MT.h"
#include <vector>

class BlackScholesMCPricer {
// Arguments permettant d'obtenir le prix de l'option � l'aide de la m�thode de Mont Carlo 
private:
    Option* _option;           // Pointeur vers l'option
    double _initialPrice;      // Prix initial de l'actif
    double _interestRate;      // Taux sans risque
    double _volatility;        // Volatilit�
    int _nbPathsGenerated;     // Nombre de chemins g�n�r�s
    double _currentEstimate;   // Estimation actuelle du prix
    double _sumOfSquares;      // Somme des carr�s des payoffs

public:
    // Constructeur de notre classe 
    BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility);

    // Impl�mentation des m�thodes de notre classe

    // Getter pour obtenir le nombre de chemins g�n�r�s
    int getNbPaths() const;

    // G�n�re des chemins Monte Carlo
    void generate(int nb_paths);

    // Retourner l'estimation actuelle du prix de l'option
    double operator()() const;

    // Calculer l'intervalle de confiance � 95 % 
    std::vector<double> confidenceInterval() const;
};
