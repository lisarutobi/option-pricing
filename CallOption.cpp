#include "CallOption.h"
#include <algorithm>

// Impl�mentation de notre constructeur 
CallOption::CallOption(double expiry, double strike):EuropeanVanillaOption(expiry, strike){}

// Impl�mentation des m�thodes de la classe CallOption

// M�thode qui retourne le prix d'un call d'une option Europ�enne 
double CallOption::payoff(double spotPrice) const  
{
	return std::max(spotPrice - getStrike(), 0.0);
}

optionType CallOption::GetOptionType() const
{
	return optionType::Call;
}