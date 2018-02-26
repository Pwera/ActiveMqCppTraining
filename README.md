<h2>Build instruction:</h2>

```
mkdir build
cd build
cmake ..
cmake --build . --target install
```

Features:
- CMake as build system generator
- Unit tests coverage
- CppCheck integration
- Installation process

You can use this library in your project like this<br>
```
cmake_minimum_required(VERSION 3.0)
project(SampleApp)
#list(APPEND CMAKE_PREFIX_PATH "INSTALLATION_DIRECTORY")
set(CMAKE_CXX_STANDARD 11)
find_package(ActiveMQ REQUIRED)
add_executable(SampleApp main.cpp)
target_link_libraries(SampleApp ActiveMqTraining::Decaf)
```
