Requirements

CMake - build tool
Windows:

https://cmake.org/download/

Linux:

sudo apt-get install cmake

Activemq-cpp library

git clone https://github.com/apache/activemq-cpp

cd activemq-cpp/activemq-cpp

sh autogen.sh

./configure && make -j4 && make install
