cmake_minimum_required(VERSION 3.23)
project(project_part2)

set(CMAKE_CXX_STANDARD 20)

#add_subdirectory(lib/googletest-1.14.0)
#include_directories(lib/googletest-1.14.0/googletest/include)
#add_executable(run_test tests/funcTest.cpp internal/methods.h)
#target_link_libraries(run_test gtest gtest_main)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -fopenmp")
add_executable(app main.cpp)
add_executable(doFiles files/doFiles.cpp)
