//
// Created by Didier on 25/02/2022.
//

#include "Time.hpp"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

//Constructor of the class, instantiate the private variable beginTime to the current Time
Time::Time() : beginTime(clock_::now()) {}

//Sets the value of beginTime to the current Time
void Time::reset() {
    beginTime = clock_::now();
}

//Returns the time elapsed between beginTime and the current Time
double Time::elapsed() const {
    return std::chrono::duration_cast<second_> (clock_::now() - beginTime).count();
}

//Returns a string representing the current date and time as following : Month/Day/Year at HH:MM:SS.ms
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

string Time::getCurrentDate() {
    // Get current time
    time_point<clock_> now = clock_::now();

    // Get the number of milliseconds for the current second
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    // Convert to time_t in order to convert to decomposed time right after
    long timer = system_clock::to_time_t(now);

    // Convert to decomposed time
    tm decomposedTime = *std::localtime(&timer);

    ostringstream oss;

    oss << std::put_time(&decomposedTime, "%D"); // Day

    return oss.str();
}

string Time::getCurrentTime() {
    // Get current time
    time_point<clock_> now = clock_::now();

    // Get the number of milliseconds for the current second
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    // Convert to time_t in order to convert to decomposed time right after
    long timer = system_clock::to_time_t(now);

    // Convert to decomposed time
    tm decomposedTime = *std::localtime(&timer);

    ostringstream oss;

    oss << std::put_time(&decomposedTime, "%H:%M:%S"); // HH:MM:SS
    oss << '.' << setfill('0') << setw(3) << ms.count();

    return oss.str();
}
