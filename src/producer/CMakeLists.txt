cmake_minimum_required(VERSION 3.5)
project(Producer)

set(SOURCE_FILES main.cpp producer.hpp)

add_executable(Producer ${SOURCE_FILES})

target_link_libraries(Producer ${ACTIVEMQ_LIBRARIES})