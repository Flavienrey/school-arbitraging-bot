//
// Created by Didier on 25/02/2022.
//

#include "Time.hpp"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

Time::Time() : beginTime(clock_::now()) {}

void Time::reset() {
    beginTime = clock_::now();
}

double Time::elapsed() const {
    return std::chrono::duration_cast<second_> (clock_::now() - beginTime).count();
}

string Time::getCurrentDateAndTime()
{
    // Get current time
    time_point<clock_> now = clock_::now();

    // Get the number of milliseconds for the current second
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    // Convert to time_t in order to convert to decomposed time right after
    long timer = system_clock::to_time_t(now);

    // Convert to decomposed time
    tm decomposedTime = *std::localtime(&timer);

    ostringstream oss;

    oss << std::put_time(&decomposedTime, "%D at %H:%M:%S"); // HH:MM:SS
    oss << '.' << setfill('0') << setw(3) << ms.count();

    return oss.str();
}