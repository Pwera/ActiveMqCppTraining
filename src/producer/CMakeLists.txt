cmake_minimum_required(VERSION 3.3)
project(Producer)

set(SOURCE_FILES main.cpp producer.hpp)

add_executable(Producer ${SOURCE_FILES})

target_link_libraries(Producer ActiveMqCpp)
target_compile_options(Producer PRIVATE -std=c++14 -Wno-deprecated-declarations) #TODO: Wno-deprecated-declarations fot auto-ptr