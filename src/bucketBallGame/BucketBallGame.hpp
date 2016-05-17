#ifndef ACTIVEMQTRAINING_BUCKETBALLGAME_HPP
#define ACTIVEMQTRAINING_BUCKETBALLGAME_HPP

#include "../ActiveMq.hpp"



class BucketBallGame : public Runnable {
private:
    int bucket[2] = {10000, 10000};
    static const bool RIGHT_TO_LEFT=false;
    bool direction;
public:
//   static List<Thread*> *listOfThreads ;
   static  std::vector<Thread*> vec;
public:
    BucketBallGame(bool direction) : direction(direction) { }

    static void doTransform() {
        for (int i = 0; i < 100; i++) {
            vec.emplace_back(new Thread(new BucketBallGame( !RIGHT_TO_LEFT)));
            vec.emplace_back(new Thread(new BucketBallGame(RIGHT_TO_LEFT)));
            }
//        for(int i =0;i<listOfThreads->size();i++){
            //listOfThreads->get(i)->start();
            //listOfThreads->get(i)->join();
//        }
        for(auto &&th: vec){
            th->start();
            th->join();
        }



    }
  void  transfer(bool direction, int numToTransfer) {
     if (direction == RIGHT_TO_LEFT) {
         bucket[0] += numToTransfer;
         bucket[1] -= numToTransfer;
         std::cout<<"0 " <<bucket[0]<< " " <<bucket[1] <<"\n";
         Thread::sleep(3000 * Math::random());
     } else {
         bucket[0] -= numToTransfer;
         bucket[1] += numToTransfer;
         std::cout<<"1 " <<bucket[0]<< " " <<bucket[1] <<"\n";
         Thread::sleep(100 * Math::random());
     }
     std::cout << "Total: " << (bucket[0] + bucket[1]) << std::endl;

 }

    virtual void run() override final {
        for (int i = 0; i < 1000000; ++i) {
            transfer(direction, 1);
        }
        try {
            //Thread::sleep(1);
        }catch(InterruptedException& ex){
            ex.printStackTrace(std::cout);
        }
    }

};
std::vector<Thread*> BucketBallGame::vec{};


#endif //ACTIVEMQTRAINING_BUCKETBALLGAME_HPP
