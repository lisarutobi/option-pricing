#pragma once

#include "Option.h"

class BlackScholesPricer {
private:
    Option* _option;       // Pointeur vers l'option (peut �tre une option digitale ou vanilla)
    double _asset_price;   
    double _interest_rate; 
    double _volatility;    

    // M�thodes utilitaires
    double normalCDF(double x) const; 
    double normalPDF(double x) const; 

public:
    // Constructeur de notre classe BlackScholesPricer
    BlackScholesPricer(Option* option, double asset_price, double interest_rate, double volatility);

    // Methode pour calculer le prix de l'option
    double operator()() const;

    // M�thode pour calculer le delta de notre option 
    double delta() const;
};
