cmake_minimum_required(VERSION 3.3)
project(BucketBallGame)

set(SOURCE_FILES main.cpp BucketBallGame.hpp)

add_executable(BucketBallGame ${SOURCE_FILES})
target_link_libraries(BucketBallGame ActiveMqCpp)
target_compile_options(BucketBallGame PRIVATE -std=c++14 -Wno-deprecated-declarations) #TODO: Wno-deprecated-declarations fot auto-ptr