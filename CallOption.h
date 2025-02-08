#pragma once
#include "EuropeanVanillaOption.h"


class CallOption:public EuropeanVanillaOption
{
public:
	CallOption(double expiry, double strike); // constructeur

	// D�finition des m�thodes
	double payoff(double spotPrice) const override;
	optionType GetOptionType() const override;
	

};

