//
// Created by Parth Parakh on 12/01/21.
//

#ifndef OPTIONPRICING_CPPCON19_EQUITYPRICEGENERATOR_H
#define OPTIONPRICING_CPPCON19_EQUITYPRICEGENERATOR_H

#include<vector>

class EquityPriceGenerator
{
private:
    double dt;
    const double initEquityPrice;
    unsigned numTimeSteps;
    double drift;
    double volatility;
public:
    EquityPriceGenerator()= default;
    EquityPriceGenerator(double initEquityPrice_, unsigned numTimeSteps_, double timeToExpiry_, double drift_, double volatilty_ );
    std::vector<double> operator()(int seed) const;
};

#endif //OPTIONPRICING_CPPCON19_EQUITYPRICEGENERATOR_H
