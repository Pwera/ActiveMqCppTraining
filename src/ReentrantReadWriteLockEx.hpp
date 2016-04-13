#include <iostream>
#include <string>
#include <decaf/util/concurrent/locks/ReentrantReadWriteLock.h>
#include <decaf/lang/Runnable.h>
#include <decaf/lang/Thread.h>
#include <decaf/lang/exceptions/InterruptedException.h>

using namespace decaf::util::concurrent::locks;
using namespace decaf::lang::exceptions;
using namespace decaf::lang;
using namespace std;

class ReentrantReadWriteLockExample {

static ReentrantReadWriteLock lock;

static  std::string message;


public:
    ReentrantReadWriteLockExample()  {
        ReentrantReadWriteLock* lock =new ReentrantReadWriteLock();
    }

private:
    class Read :public Runnable {

    public:
        virtual void run() {
            for(int i = 0; i<= 10; i ++) {
                if(lock.isWriteLocked()) {
                    std::cout<<"I'll take the lock from Write\n";
                }
                lock.readLock().lock();
//                std::cout<<"ReadThread " + Thread.currentThread().getId() + " ---> Message is " + message );
                lock.readLock().unlock();
            }
        }
    };

    class WriteA : public Runnable {
    public:
        virtual void run() {
            for(int i = 0; i<= 10; i ++) {
                try {
                    lock.writeLock().lock();
                    message = message+"a";
                } catch(...){
                        lock.writeLock().unlock();
                }
            }
        }
    };

     class WriteB : public Runnable {
        public :
        virtual void run() {
            for(int i = 0; i<= 10; i ++) {
                try {
                    lock.writeLock().lock();
                    message = message +"b";
                } catch(...) {
                        lock.writeLock().unlock();
                }
            }
        }
    };
public :
    void start(){
        try{
            Runnable* r1 = new Read();
            Thread *t1 = new Thread(r1);
            Runnable* r2 = new WriteA();
            Thread *t2 = new Thread(r2);
            Runnable* r3 = new WriteB();
            Thread *t3 = new Thread(r3);
            t1->start();
            t2->start();
            t3->start();
            t1->join();
            t2->join();
            t3->join();
        }
        catch (InterruptedException& ex){

        }
    }
};