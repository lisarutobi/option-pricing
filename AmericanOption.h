#pragma once
#include "Option.h"

// Definition du 1er type d'option, les options Américaines
class AmericanOption : public Option {
public:
    //Définition du destructeur
    AmericanOption(double expiry);
    virtual ~AmericanOption() {}

    //Définition des différentes méthodes
    bool isAmericanOption() const override;

    double payoffPath(const std::vector<double>& path) const override {
        return payoff(path.back());
    }
};
