#include <iostream>
#include <random>
#include"MCEuroOptPricer.h"

using std::vector;
using std::cout;
using std::endl;
using std::for_each;
using std::transform;
using std::generate;
using std::generate_n;
using std::fill;
using std::fill_n;
using std::mt19937_64;
using std::normal_distribution;

void mcOptionTestNotParallel(double tau, int numTimeSteps, int numScenarios, int initSeed = 100);
void mcOptionTestRunParallel(double tau, int numTimeSteps, int numScenarios, int initSeed = 100);

int main() {

    mcOptionTestNotParallel(1.0, 12, 10000);
    mcOptionTestRunParallel(1.0, 12, 10000);

    return 0;
}

void mcOptionTestNotParallel(double tau, int numTimeSteps, int numScenarios, int initSeed)
{

    double strike = 102.0;
    double spot = 100.0;
    double riskFreeRate = 0.025;
    double volatility = 0.06;
    double quantity = 7000.00;	// 1.0;

    MCEuroPricer qlCall(strike, spot, riskFreeRate, volatility, tau,OptionType::CALL, numTimeSteps,
                           numScenarios, false, initSeed, quantity);

    double res = qlCall();
    cout << "Number of time steps = " << numTimeSteps << "; number of scenarios = " << numScenarios << endl;
    cout << "Runtime (NOT in parallel) = " << qlCall.time_() << "; price = " << res << endl << endl;
}

void mcOptionTestRunParallel(double tau, int numTimeSteps, int numScenarios, int initSeed)
{
    cout << endl << "--- mcOptionTestRunParallel(.) ---" << endl;
    double strike = 102.0;
    double spot = 100.0;
    double riskFreeRate = 0.025;
    double volatility = 0.06;
    double quantity = 7000.00;
    OptionType call = OptionType::CALL;

    MCEuroPricer qlCall(strike, spot, riskFreeRate, volatility, tau,
                           call, numTimeSteps, numScenarios, true, initSeed, quantity);

    double res = qlCall();
    cout << "Number of time steps = " << numTimeSteps << "; number of scenarios = " << numScenarios << endl;
    cout << "Runtime (IS RUN in parallel) = " << qlCall.time_() << "; price = " << res << endl << endl;
}