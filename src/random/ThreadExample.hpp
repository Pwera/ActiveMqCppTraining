#ifndef ACTIVEMQTRAINING_THREADEXAMPLE_HPP
#define ACTIVEMQTRAINING_THREADEXAMPLE_HPP

#include "../ActiveMq.hpp"
#include <cassert>
#include <memory>

class SimpleThread : public Runnable {
private:
    int delay;
public:
    decaf::util::concurrent::Mutex lock;

    virtual void run() {
        try {

            synchronized(&lock) {
                    lock.notify();
                    lock.wait(delay);
                }

        } catch (decaf::lang::exceptions::InterruptedException &e) {
            return;
        }
    }

    SimpleThread(int d) : delay(0), lock() {
        if (d >= 0) {
            delay = d;
        }
    }

    virtual ~SimpleThread() { }
};

class ThreadEx1 {
    std::unique_ptr<Runnable> r{new SimpleThread(10)};
public:
    void construct1() {
        Thread thread(r.get(), "SimpleThread");
        assert(thread.getName() == "SimpleThread");
        thread.start();
        thread.join();
    }

    void construct2() {
        Thread thread("SimpleThread");
        assert(thread.getName() == "SimpleThread");
        thread.start();
        thread.join();

    }

    void testPriority() {
        Thread th(r.get());
        assert(th.getPriority() == Thread::NORM_PRIORITY);
//        th.setPriority(Thread::MAX_PRIORITY);
//        assert(th.getPriority() == Thread::MIN_PRIORITY);
        th.start();
        th.join();

    }

    void testIsAlive() {
        std::unique_ptr<SimpleThread> r{new SimpleThread(10)};
        Thread th(r.get());
        assert(!th.isAlive());

        synchronized(&(r->lock)) {
                th.start();
                try {
                    r->lock.wait();
                } catch (InterruptedException &e) {

                }
            };
        assert(th.isAlive());

        try {
            th.join();
        } catch (InterruptedException &e) {

        }
        assert(!th.isAlive());
    }
    void testState(){
        std::unique_ptr<SimpleThread> r{new SimpleThread(10)};
        Thread th{r.get()};
        assert(!th.isAlive());
        synchronized(&(r.get()->lock)){
                th.start();
                try{
                    r->lock.wait();
                }catch(InterruptedException& ex){

                }
            }

        assert(th.isAlive());
        assert(th.getState()==Thread::TIMED_WAITING);
        try{
            th.join();
        }catch(InterruptedException& ex){

        }
        assert(!th.isAlive());
        assert(th.getState()==Thread::TERMINATED);

    }
};

#endif //ACTIVEMQTRAINING_THREADEXAMPLE_HPP
