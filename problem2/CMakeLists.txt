cmake_minimum_required(VERSION 2.6)
project(problem2)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra")

include_directories(include)

add_executable(problem2
    main.cpp
    src/distribution_factory.cpp
    src/bernoulli.cpp)

