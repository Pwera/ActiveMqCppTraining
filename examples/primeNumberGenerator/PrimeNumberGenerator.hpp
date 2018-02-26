#ifndef ACTIVEMQTRAINING_PRIMENUMBERGENERATOR_HPP
#define ACTIVEMQTRAINING_PRIMENUMBERGENERATOR_HPP

#include "../ActiveMq.hpp"
#include <memory>

class WorkerThread : public Runnable {

public:
    virtual void run() override {
        long i = 1;
        while (true) {
            long j;
            for (j = 2; j < i; j++) {
                long n = i % j;
                if (n == 0) { break; }
            }
            if (i == j) {
                std::cout << " " << i << std::endl;
            }
            i++;
        }
    }
};

class PrimeNumberGenerator {
    std::unique_ptr<Runnable> r;
    std::unique_ptr<Thread> primeNumberGenerator;
public:
    PrimeNumberGenerator() : r{new WorkerThread()} {
        primeNumberGenerator.reset(new Thread{r.get()});

        primeNumberGenerator->start();
        try {
            Thread::sleep(10);
        } catch (InterruptedException &ex) {
            ex.printStackTrace(std::cout);
        }
    }
};

#endif //ACTIVEMQTRAINING_PRIMENUMBERGENERATOR_HPP
