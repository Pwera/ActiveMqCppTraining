cmake_minimum_required(VERSION 3.3)
project(Consumer)
set(SOURCE_FILES main.cpp consumer.hpp)
add_executable(Consumer ${SOURCE_FILES})
target_link_libraries(Consumer ActiveMqCpp)
target_compile_options(Consumer PRIVATE -std=c++14 -Wno-deprecated-declarations) #TODO: Wno-deprecated-declarations fot auto-ptr