cmake_minimum_required(VERSION 2.6)
project(problem3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIERD ON)

include_directories(include)

add_executable(task1 task1.cpp)
add_executable(task2 task2.cpp)

target_link_libraries(task1 pthread) 
target_link_libraries(task2 pthread gtest)

target_include_directories(task2 PRIVATE
    third-party/googletest/googletest/include)

add_subdirectory(third_party/googletest)

