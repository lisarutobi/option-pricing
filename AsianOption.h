#pragma once
#include "Option.h"
#include <vector>
#include <numeric> 

class AsianOption : public Option {
private:
    std::vector<double> _fixingDates; // Dates de fixation // Timestamps (t1, ..., tm)

public:
    // Constructeur
    AsianOption(const std::vector<double>& fixing_dates);

    // Impl�mentations des m�thodes de notre classe AsianOption
    // Getter pour les timestamps
    const std::vector<double>& getFixingDates() const;

    // Override des m�thodes de `Option`
    double getExpiry() const override;                  
    bool isAsianOption() const override;                
    double payoffPath(const std::vector<double>& path) const override; 
};