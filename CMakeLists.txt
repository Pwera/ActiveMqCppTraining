cmake_minimum_required(VERSION 3.3)
project(ActiveMqTraining)

add_subdirectory(external/activemq-cpp/activemq-cpp)

add_subdirectory(src/primeNumberGenerator)
add_subdirectory(src/bucketBallGame)
add_subdirectory(src/consumer)
add_subdirectory(src/producer)
add_subdirectory(src/random)