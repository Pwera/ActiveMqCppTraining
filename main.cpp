#include <iostream>
#include "src/ReentrantReadWriteLockEx.hpp"
#include "src/ReentrantLockEx.hpp"
#include "src/ThreadExample.hpp"

using namespace std;
using namespace activemq;

int main() {
    activemq::library::ActiveMQCPP::initializeLibrary();
//    ReentrantReadWriteLockExample reentrantReadWriteLockExample;
//    reentrantReadWriteLockExample.start();
    ReentrantLockEx reentrantLockEx;
    reentrantLockEx.start();
    //#########################
    ThreadEx1 thex1;
    thex1.construct1();
    thex1.construct2();
    thex1.testPriority();
    thex1.testIsAlive();
    thex1.testState();
    cout<<"1\n";
    //############################

    activemq::library::ActiveMQCPP::shutdownLibrary();
    return 0;
}