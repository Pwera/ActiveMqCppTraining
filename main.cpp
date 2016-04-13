#include <iostream>
#include "src/ReentrantReadWriteLockEx.hpp"
#include <activemq/library/ActiveMQCPP.h>
using namespace std;
using namespace activemq;

int main() {
    activemq::library::ActiveMQCPP::initializeLibrary();
    ReentrantReadWriteLockExample reentrantReadWriteLockExample;
    reentrantReadWriteLockExample.start();
    activemq::library::ActiveMQCPP::shutdownLibrary();
    return 0;
}