#include "CallOption.h"
#include <algorithm>

// Implémentation de notre constructeur 
CallOption::CallOption(double expiry, double strike):EuropeanVanillaOption(expiry, strike){}

// Implémentation des méthodes de la classe CallOption

// Méthode qui retourne le prix d'un call d'une option Européenne 
double CallOption::payoff(double spotPrice) const  
{
	return std::max(spotPrice - getStrike(), 0.0);
}

optionType CallOption::GetOptionType() const
{
	return optionType::Call;
}