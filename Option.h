#pragma once
#include "optionType.h"
#include "iostream"
#include <vector>
class Option
{
private:
	double _expiry;
	

public:
	Option(double expiry);

	virtual optionType GetOptionType() const = 0;
	virtual double getExpiry() const;
	virtual double payoff(double spotPrice) const = 0;
	virtual bool isAsianOption() const;
	virtual double payoffPath(const std::vector<double>& path) const;
	virtual bool isAmericanOption() const;
	virtual ~Option(){}
	
};

