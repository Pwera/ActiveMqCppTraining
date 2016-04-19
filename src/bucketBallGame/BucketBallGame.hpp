#ifndef ACTIVEMQTRAINING_BUCKETBALLGAME_HPP
#define ACTIVEMQTRAINING_BUCKETBALLGAME_HPP

#include "../ActiveMq.hpp"

class TransferedThread : public Runnable {
private:
    bool direction;


public:
    friend class BucketBallGame;
    TransferedThread(bool direction) : direction(direction) { }



    virtual void run() override final {
        for (int i = 0; i < 100; ++i) {
            transfer(direction, static_cast<int> (Math::random()*2000));
        }
        try {
            Thread::sleep(static_cast<int>(Math::random() * 100));
        }catch(InterruptedException& ex){
            ex.printStackTrace(std::cout);
        }
    }


};

class BucketBallGame {
private:
    static int bucket[2] = {10000, 10000};
    static const bool RIGHT_TO_LEFT=false;
public:
    friend class TransferedThread;
    void doTransform() {
        for (int i = 0; i < 10; i++) {
            Thread *th = new Thread(new TransferedThread( !RIGHT_TO_LEFT));
            Thread *th2 = new Thread(new TransferedThread( RIGHT_TO_LEFT));
            th->start();
            th2->start();
        }

    }
 static void  transfer(bool direction, int numToTransfer) {
     if (direction == RIGHT_TO_LEFT) {
         bucket[0] += numToTransfer;
         bucket[1] -= numToTransfer;
     } else {
         bucket[0] -= numToTransfer;
         bucket[1] += numToTransfer;
     }
     std::cout << "Total: " << (bucket[0] + bucket[1]) << std::endl;
 }
};


#endif //ACTIVEMQTRAINING_BUCKETBALLGAME_HPP
