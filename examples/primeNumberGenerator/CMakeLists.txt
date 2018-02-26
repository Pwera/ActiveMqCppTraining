cmake_minimum_required(VERSION 3.3)
project(PrimeNumberGenerator)
set(SOURCE_FILES main.cpp PrimeNumberGenerator.hpp)
add_executable(PrimeNumberGenerator ${SOURCE_FILES})
target_link_libraries(PrimeNumberGenerator ActiveMqCpp)
target_compile_options(PrimeNumberGenerator PRIVATE -std=c++14 -Wno-deprecated-declarations) #TODO: Wno-deprecated-declarations fot auto-ptr