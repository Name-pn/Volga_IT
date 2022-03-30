cmake_minimum_required(VERSION 3.21)
project(volga)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Release)

add_executable(volga main.cpp libs/task/fairy_tail.cpp libs/matrix/matrix.cpp libs/solver/solve.cpp libs/solver/solve.h)
