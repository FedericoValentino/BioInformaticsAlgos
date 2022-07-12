cmake_minimum_required(VERSION 3.22)
project(BioInformatics)

set(CMAKE_CXX_STANDARD 23)

add_executable(HierHolzer HierHolzer/HierHolzer.cpp)

add_executable(Edit EditDistance/EditDistance.cpp)
