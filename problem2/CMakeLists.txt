cmake_minimum_required(VERSION 2.6)
project(problem2)

set(CXX_STANDARD 17)
set(CXX_FLAGS "-Wall -Wextra")

include_directories(include)

add_executable(problem2 main.cpp
    src/bernoulli.cpp)

