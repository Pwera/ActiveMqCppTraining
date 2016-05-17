#include "../ActiveMq.hpp"
#include "BucketBallGame.hpp"

int main(){
    ActiveMqInit ActiveMqInit;

    BucketBallGame::doTransform();
    Thread::sleep(static_cast<int>(Math::random() * 3000));


}