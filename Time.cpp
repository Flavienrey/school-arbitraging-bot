//
// Created by Didier on 25/02/2022.
//

#include "Time.hpp"
#include <chrono>

Time::Time() : beginTime(clock_::now()) {

}

void Time::reset() {
    beginTime = clock_::now();
}

double Time::elapsed() const {
    return std::chrono::duration_cast<second_> (clock_::now() - beginTime).count();
}