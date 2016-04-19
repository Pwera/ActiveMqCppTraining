cmake_minimum_required(VERSION 3.5)
project(ActiveMqTraining)

link_directories(/usr/local/lib64)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
set(ACTIVEMQ_CXX_FLAGS "-DLINUX -D_REENTRANT -D_GNU_SOURCE -pthread -I/usr/local/include/activemq-cpp-3.10.0 -I/usr/include/apr-1 -L/usr/local/lib64 -lactivemq-cpp -lpthread -ldl -luuid ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ACTIVEMQ_CXX_FLAGS}")
set(SOURCE_FILES main.cpp src/ReentrantReadWriteLockEx.hpp src/ReentrantLockEx.hpp src/ActiveMq.hpp src/ThreadExample.hpp)


add_subdirectory(src/chat)
add_subdirectory(src/primeNumberGenerator)
add_subdirectory(src/bucketBallGame)

add_executable(ActiveMqTraining ${SOURCE_FILES})
target_link_libraries(ActiveMqTraining -lactivemq-cpp)