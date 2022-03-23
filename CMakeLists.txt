cmake_minimum_required(VERSION 3.21.5)
project(Bot_d_arbitrage)

set(CMAKE_CXX_STANDARD 17)

add_executable(Bot_d_arbitrage main.cpp Graph.cpp GraphTests.cpp BellmanFordTests.cpp Time.cpp httpGetFunctions.cpp)
include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git GIT_TAG beb9e98806bb84bcc130a2cebfbcbbc6ce62b335) # The commit hash for 1.7.2. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

target_link_libraries(Bot_d_arbitrage PRIVATE cpr::cpr)