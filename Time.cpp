//
// Created by Didier on 25/02/2022.
//

#include "Time.hpp"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;
using namespace chrono;

Time::Time() : beginTime(clock_::now()) {

}

void Time::reset() {
    beginTime = clock_::now();
}

double Time::elapsed() const {
    return std::chrono::duration_cast<second_> (clock_::now() - beginTime).count();
}

string Time::time_in_HH_MM_SS_MMM()
{
    // get current time
    auto now = clock_::now();

    // get number of milliseconds for the current second
    // (remainder after division into seconds)
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    // convert to std::time_t in order to convert to std::tm (broken time)
    auto timer = system_clock::to_time_t(now);

    // convert to broken time
    tm bt = *std::localtime(&timer);

    ostringstream oss;

    oss << std::put_time(&bt, "%H:%M:%S"); // HH:MM:SS
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();

    return oss.str();
}