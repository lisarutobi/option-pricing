#ifndef CRRPRICER_H
#define CRRPRICER_H

#include "Option.h"
#include "BinaryTree.h"

class CRRPricer {
private:
    Option* _option;
    int _depth;
    double _S0;
    double _U;
    double _D;
    double _R;
    double _q;
    double _interest_rate;  
    double _volatility;     
    bool _computed;

    BinaryTree<double> _priceTree;
    BinaryTree<double> _valueTree;
    BinaryTree<bool> _exerciseTree;

    void checkArbitrage();
    void buildPriceTree();
    void buildValueTree();
    double computeClosedForm() const;
   

public:
    // Constructeur pour paramètres explicites (U, D, R donnés)
    CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate);

    // Constructeur pour approximation Black-Scholes (calcul de U, D, R à partir de r et sigma)
    CRRPricer(Option* option, int depth, double asset_price, double interest_rate, double volatility);

    // Getter afin d'obtenir une valeur dans l arbre
    double get(int n, int i) const;

    // Getter afin de récupérer la politique d'exercice
    bool getExercise(int n, int i) const;

    // Calculer le prix de l'option
    double operator()(bool closed_form = false);

    void compute();
};

#endif // CRRPRICER_H

