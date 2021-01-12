cmake_minimum_required(VERSION 3.17)
project(OptionPricing_CPPCON19)

set(CMAKE_CXX_STANDARD 17)

add_executable(OptionPricing_CPPCON19 main.cpp EquityPriceGenerator.cpp EquityPriceGenerator.h MCEuroOptPricer.h MCEuroOptPricer.cpp)