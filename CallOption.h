#pragma once
#include "EuropeanVanillaOption.h"


class CallOption:public EuropeanVanillaOption
{
public:
	CallOption(double expiry, double strike); // constructeur

	// Définition des méthodes
	double payoff(double spotPrice) const override;
	optionType GetOptionType() const override;
	

};

