#include "../ActiveMq.hpp"
#include "consumer.hpp"
int main(){
    ActiveMqInit ActiveMqInit;


    std::string brokerURI =
//            "failover:(tcp://192.168.0.102:8161?wireFormat=stomp"
                    "failover://(tcp://192.168.56.1:61616?wireFormat=openwire"

//        "?wireFormat=openwire"
//        "&connection.useAsyncSend=true"
//        "&transport.commandTracingEnabled=true"
//        "&transport.tcpTracingEnabled=true"
//        "&wireFormat.tightEncodingEnabled=true"
                    ")";
    std::string destURI = "SAMPLEQUEUE"; //?consumer.prefetchSize=1";
    bool useTopics = false;

    //============================================================
    // set to true if you want the consumer to use client ack mode
    // instead of the default auto ack mode.
    //============================================================
    bool clientAck = false;

    // Create the consumer
    Consumer consumer( brokerURI, destURI, useTopics, clientAck );

    // Start it up and it will listen forever.
    consumer.runConsumer();

    // Wait to exit.
    std::cout << "Press 'q' to quit" << std::endl;
    while( std::cin.get() != 'q') {}

    // All CMS resources should be closed before the library is shutdown.
    consumer.close();

    std::cout << "-----------------------------------------------------\n";
    std::cout << "Finished with the example." << std::endl;
    std::cout << "=====================================================\n";


}