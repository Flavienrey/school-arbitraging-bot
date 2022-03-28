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

    /**
    Constructor of the class, instantiate the private variable beginTime to the current Time
    @return the instanced class
    */
    Time();


    /**
    Sets the value of beginTime to the current Time
    */
    void reset();


    /**
    @return the time elapsed between beginTime and the current Time
    */
    double elapsed() const;


    /**
    @return a string representing the current date and time as following : Month/Day/Year at HH:MM:SS.ms
    */
    static string getCurrentDateAndTime();
};


#endif //BOT_D_ARBITRAGE_TIME_HPP
