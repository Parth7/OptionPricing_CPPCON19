//
// Created by Parth Parakh on 12/01/21.
//

#include "EquityPriceGenerator.h"
#include<random>
#include<algorithm>
#include<ctime>
#include<cmath>

using std::vector;
using std::mt19937_64;
using std::normal_distribution;
using std::exp;

EquityPriceGenerator::EquityPriceGenerator(double initEquityPrice_, unsigned int numTimeSteps_, double timeToExpiry_,
                                           double drift_, double volatilty_) : initEquityPrice(initEquityPrice_),
                                           numTimeSteps(numTimeSteps_), dt(timeToExpiry_/numTimeSteps_), drift(drift_),
                                           volatility(volatilty_) {}

vector<double> EquityPriceGenerator::operator()(int seed) const
{
    vector<double> v;
    mt19937_64 mtEngine(seed);
    normal_distribution<> nd;

    auto newPrice = [this](double previousEquityPrice, double norm)
    {
        double price;
        double expArg1 = (drift - ((volatility * volatility) / 2.0)) * dt;
        double expArg2 = volatility * norm * sqrt(dt);
        return price = previousEquityPrice * exp(expArg1 + expArg2);
    };

    v.push_back(initEquityPrice);
    double equityprice  = initEquityPrice;
    for(int i=0;i<=numTimeSteps;i++)
    {
        equityprice = newPrice(equityprice,nd(mtEngine));
        v.push_back(equityprice);
    }
    return v;
}


