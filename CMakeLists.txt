cmake_minimum_required(VERSION 3.7.2)
project(Bot_d_arbitrage)

set(CMAKE_CXX_STANDARD 14)

add_executable(Bot_d_arbitrage main.cpp Graph.cpp GraphTests.cpp)
