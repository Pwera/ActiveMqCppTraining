#pragma once
#include "../ActiveMq.hpp"
#include <string>
using namespace std;

class Producer : public Runnable {
private:

    Connection* connection;
    Session* session;
    Destination* destination;
    MessageProducer* producer;
    bool useTopic;
    bool clientAck;
    unsigned int numMessages;
    std::string brokerURI;
    std::string destURI;

private:

    Producer( const Producer& );
    Producer& operator= ( const Producer& );

public:

    Producer( const std::string& brokerURI, unsigned int numMessages,
                    const std::string& destURI, bool useTopic = false, bool clientAck = false ) :
            connection(nullptr),
            session(nullptr),
            destination(nullptr),
            producer(nullptr),
            useTopic(useTopic),
            clientAck(clientAck),
            numMessages(numMessages),
            brokerURI(brokerURI),
            destURI(destURI) {
    }

    virtual ~Producer(){
        cleanup();
    }

    void close() {
        this->cleanup();
    }

    virtual void run() {
        try {

            // Create a ConnectionFactory
            unique_ptr<ActiveMQConnectionFactory> connectionFactory(
                    new ActiveMQConnectionFactory( brokerURI ) );

            // Create a Connection
            try{
                connection = connectionFactory->createConnection();
                connection->start();
            } catch( CMSException& e ) {
                e.printStackTrace();
                throw e;
            }

            // Create a Session
            if( clientAck ) {
                session = connection->createSession( Session::CLIENT_ACKNOWLEDGE );
            } else {
                session = connection->createSession( Session::AUTO_ACKNOWLEDGE );
            }
//            connection->getMetaData()->getCMSMajorVersion();

            // Create the destination (Topic or Queue)
            if( useTopic ) {
                destination = session->createTopic( destURI );
            } else {
                destination = session->createQueue( destURI );
            }

            // Create a MessageProducer from the Session to the Topic or Queue
            producer = session->createProducer( destination );
            producer->setDeliveryMode( DeliveryMode::NON_PERSISTENT );

            // Create the Thread Id String
            string threadIdStr = Long::toString( Thread::currentThread()->getId() );

            // Create a messages
            string text = (string)"Hello world! from thread " + threadIdStr;

            for( unsigned int ix=0; ix<numMessages; ++ix ){
                TextMessage* message = session->createTextMessage( text );

                message->setIntProperty( "Integer", ix );

                // Tell the producer to send the message
                printf( "Sent message #%d from thread %s\n", ix+1, threadIdStr.c_str() );
                producer->send( message );

                delete message;
            }

        }catch ( CMSException& e ) {
            e.printStackTrace();
        }
    }

private:

    void cleanup(){

        // Destroy resources.
        try{
            if( destination != nullptr ) delete destination;
        }catch ( CMSException& e ) { e.printStackTrace(); }
        destination = nullptr;

        try{
            if( producer != nullptr ) delete producer;
        }catch ( CMSException& e ) { e.printStackTrace(); }
        producer = nullptr;

        // Close open resources.
        try{
            if( session != nullptr ) session->close();
            if( connection != nullptr ) connection->close();
        }catch ( CMSException& e ) { e.printStackTrace(); }

        try{
            if( session != nullptr ) delete session;
        }catch ( CMSException& e ) { e.printStackTrace(); }
        session = nullptr;

        try{
            if( connection != nullptr ) delete connection;
        }catch ( CMSException& e ) { e.printStackTrace(); }
        connection = nullptr;
    }
};