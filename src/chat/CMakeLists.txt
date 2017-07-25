cmake_minimum_required(VERSION 3.5)
project(Chat)
set(SOURCE_FILES Chat.cpp Chat.h)
add_executable(Chat ${SOURCE_FILES})
target_link_libraries(Chat ActiveMqCpp)
target_compile_options(Chat PRIVATE -std=c++14 -Wno-deprecated-declarations) #TODO: Wno-deprecated-declarations fot auto-ptr