#pragma once
#include "Option.h"

// Definition du 1er type d'option, les options Am�ricaines
class AmericanOption : public Option {
public:
    //D�finition du destructeur
    AmericanOption(double expiry);
    virtual ~AmericanOption() {}

    //D�finition des diff�rentes m�thodes
    bool isAmericanOption() const override;

    double payoffPath(const std::vector<double>& path) const override {
        return payoff(path.back());
    }
};
