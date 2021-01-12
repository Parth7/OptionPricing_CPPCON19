//
// Created by Parth Parakh on 12/01/21.
//

#ifndef OPTIONPRICING_CPPCON19_MCEUROOPTPRICER_H
#define OPTIONPRICING_CPPCON19_MCEUROOPTPRICER_H

#include"EquityPriceGenerator.h"

enum class OptionType
{
    CALL,
    PUT
};

class MCEuroPricer
{
private:
    void calculate();
    void computeprice();
    void generate_seeds();
    double payoff(double terminalprice);

    void computepriceNonParallel();
    void computepriceAsync();

    double strike;
    double spot;
    double riskfreerate;
    double volatility;
    double timetoexpiry;
    OptionType opt;
    int numtimesteps;
    int numscenarios;
    bool runparallel=true;
    int initSeed = 106;
    double quantity = 1.0;

    double discfactor;
    double price;

    std::vector<int> seeds;
    double time;
public:
    MCEuroPricer(double strike_, double spot_, double riskfreerate_, double volatility_, double timetoexpiry_,
                 OptionType optiontype_, int numtimesteps_, int numscenarios_, bool runparallel_, int initseed_,
                 double quantity_);

    double operator()()const;
    double time_() const;
};
#endif //OPTIONPRICING_CPPCON19_MCEUROOPTPRICER_H
