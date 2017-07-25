cmake_minimum_required(VERSION 3.3)
project(ActiveMqTraining)

add_subdirectory(external/activemq-cpp/activemq-cpp)

set(SOURCE_FILES main.cpp src/ReentrantReadWriteLockEx.hpp src/ReentrantLockEx.hpp src/ActiveMq.hpp src/ThreadExample.hpp)

add_subdirectory(src/primeNumberGenerator)
add_subdirectory(src/bucketBallGame)
add_subdirectory(src/consumer)
add_subdirectory(src/producer)

add_executable(ActiveMqTraining ${SOURCE_FILES})
target_link_libraries(ActiveMqTraining ActiveMqCpp)