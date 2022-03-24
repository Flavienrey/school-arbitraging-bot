//
// Created by Didier on 25/02/2022.
//

#ifndef BOT_D_ARBITRAGE_TIME_HPP
#define BOT_D_ARBITRAGE_TIME_HPP

#include <chrono>
#include <string>

class Time {

private:

    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<double, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beginTime;

public:

    Time();

    void reset();

    double elapsed() const;

    static std::__cxx11::basic_string<char> time_in_HH_MM_SS_MMM();
};


#endif //BOT_D_ARBITRAGE_TIME_HPP
