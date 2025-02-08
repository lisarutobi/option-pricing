#include "PutOption.h"
#include <algorithm>

PutOption::PutOption(double expiry, double strike):EuropeanVanillaOption(expiry,strike){}

double PutOption::payoff(double spotPrice) const 
{
	return std::max(getStrike() - spotPrice, 0.0);
}
optionType PutOption::GetOptionType() const
{
	return optionType::Put;
}

