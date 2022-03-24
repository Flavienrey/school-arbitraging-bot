//
// Created by Didier on 25/02/2022.
//

#ifndef BOT_D_ARBITRAGE_TIME_HPP
#define BOT_D_ARBITRAGE_TIME_HPP

#include <chrono>
#include <string>
using namespace std;
using namespace chrono;

class Time {

private:

    typedef high_resolution_clock clock_;
    typedef duration<double, ratio<1> > second_;
    time_point<clock_> beginTime;

public:

    Time();

    void reset();

    double elapsed() const;

    static string time_in_HH_MM_SS_MMM();
};


#endif //BOT_D_ARBITRAGE_TIME_HPP
