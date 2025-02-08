#include "Option.h"

Option::Option(double expiry) : _expiry(expiry){}

double Option::getExpiry() const 
{
	return _expiry;
}
bool Option::isAsianOption() const {
	return false;
}
double Option::payoffPath(const std::vector<double>& path) const {
	return payoff(path.back());
}
bool Option::isAmericanOption() const {
	return false; 
}