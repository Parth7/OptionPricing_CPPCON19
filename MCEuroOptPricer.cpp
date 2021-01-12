//
// Created by Parth Parakh on 12/01/21.
//

#include"MCEuroOptPricer.h"
#include"EquityPriceGenerator.h"
#include<vector>
#include<cmath>
#include<algorithm>
#include<limits>
#include<future>
#include<ctime>
#include<numeric>

MCEuroPricer::MCEuroPricer(double strike_, double spot_, double riskfreerate_, double volatility_, double timetoexpiry_,
                           OptionType optiontype_, int numtimesteps_, int numscenarios_, bool runparallel_,
                           int initseed_, double quantity_) : strike(strike_), spot(spot_), riskfreerate(riskfreerate_),
                           volatility(volatility_), timetoexpiry(timetoexpiry_), opt(optiontype_), numtimesteps(numtimesteps_),
                           numscenarios(numscenarios_), runparallel(runparallel_), initSeed(initseed_), quantity(quantity_)
                           {
                                discfactor = std::exp(-riskfreerate * timetoexpiry );
                                calculate();
                           }

double MCEuroPricer::operator()() const
{
    return price;
}

double MCEuroPricer::time_() const
{
    return time;
}

void MCEuroPricer::calculate()
{
    std::clock_t begin = std::clock();		// begin time with threads
    computeprice();
    std::clock_t end = std::clock();		// end time with threads
    time = double(end - begin) / CLOCKS_PER_SEC;
}

void MCEuroPricer::computeprice()
{
    if(runparallel) computepriceAsync();
    else computepriceNonParallel();
}

void MCEuroPricer::computepriceNonParallel()
{
    EquityPriceGenerator epg(spot,numtimesteps,timetoexpiry,riskfreerate,volatility);
    generate_seeds();
    std::vector<double> discountedPayoffs;

    for (auto& seed : seeds)
    {
        double terminalPrice = (epg(seed)).back();
        double payoff_ = payoff(terminalPrice);
        discountedPayoffs.push_back(discfactor* payoff_);
    }

    price = quantity*(1.0/numscenarios)*std::accumulate(discountedPayoffs.begin(),discountedPayoffs.end(),0.0);
}

void MCEuroPricer::computepriceAsync()
{
    EquityPriceGenerator epg(spot,numtimesteps,timetoexpiry,riskfreerate,volatility);
    generate_seeds();
    std::vector<std::future<std::vector<double>>> future;

    for( auto &seed:seeds)
    {
        future.push_back(std::async(epg,seed));
    }

    std::vector<double> discountpayoffs;

    for(auto &f:future)
    {
        double terminalPrice = f.get().back();
        double payoff_ = payoff(terminalPrice);
        discountpayoffs.push_back(discfactor* payoff_);
    }

    price = quantity*(1.0/numscenarios) * std::accumulate(discountpayoffs.begin(), discountpayoffs.end(), 0.0);
}

void MCEuroPricer::generate_seeds()
{
    seeds.resize(numscenarios);

    std::iota(seeds.begin(), seeds.end(), initSeed);
}

double MCEuroPricer::payoff(double terminalPrice)
{
    double payoff = 0.0;
    // instead of this we could have a payoff class as composition and that class handles different payoff using base class pointer
    switch (opt)
    {
        case OptionType::CALL:
            payoff = std::max(terminalPrice - strike, 0.0);
            break;
        case OptionType::PUT:
            payoff = std::max(strike - terminalPrice, 0.0);
            break;
        default:	// This case should NEVER happen
            payoff = std::numeric_limits<double>::quiet_NaN();
            break;
    }
    return payoff;
}