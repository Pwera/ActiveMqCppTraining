cmake_minimum_required(VERSION 3.3)
project(Random)

set(SOURCE_FILES main.cpp ReentrantReadWriteLockEx.hpp ReentrantLockEx.hpp ThreadExample.hpp)
add_executable(Random ${SOURCE_FILES})
target_link_libraries(Random ActiveMqCpp)
target_compile_options(Random PRIVATE -std=c++14 -Wno-deprecated-declarations) #TODO: Wno-deprecated-declarations fot auto-ptr
