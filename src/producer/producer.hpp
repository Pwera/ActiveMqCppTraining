#pragma once
#include "../ActiveMq.hpp"
#include <string>
#include <experimental/string_view>
using namespace std;
using namespace std::experimental;

class Producer : public Runnable {
private:

    unique_ptr<Connection> connection;
    unique_ptr<Session> session;
    unique_ptr<Destination> destination;
    unique_ptr<MessageProducer> producer;
    bool useTopic;
    bool clientAck;
    unsigned int numMessages;
    string_view brokerURI;
    string_view destURI;

private:

    Producer( const Producer& );
    Producer& operator= ( const Producer& );

public:

    Producer( const string_view& brokerURI, unsigned int numMessages,
                    const string_view& destURI, bool useTopic = false, bool clientAck = false ) :
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
                    new ActiveMQConnectionFactory( brokerURI.to_string() ) );

            // Create a Connection
            try{
                connection.reset(connectionFactory->createConnection());
                connection->start();
            } catch( CMSException& e ) {
                e.printStackTrace();
                throw e;
            }

            // Create a Session
                session.reset(connection->createSession(clientAck ? Session::CLIENT_ACKNOWLEDGE:  Session::AUTO_ACKNOWLEDGE));

            // Create the destination (Topic or Queue)
            if( useTopic ) {
                destination.reset(session->createTopic( destURI.to_string()));
            } else {
                destination.reset(session->createQueue( destURI.to_string() ));
            }

            // Create a MessageProducer from the Session to the Topic or Queue
            producer.reset(session->createProducer( destination.get() ));
            producer->setDeliveryMode( DeliveryMode::NON_PERSISTENT );

            // Create the Thread Id String
            string threadIdStr = Long::toString( Thread::currentThread()->getId() );

            // Create a messages
            string text = (string)"Hello world! from thread " + threadIdStr;

            for( unsigned int ix=0; ix<numMessages; ++ix ){
                std::unique_ptr<TextMessage> message{session->createTextMessage( text )};
                message->setIntProperty( "Integer", ix );
                string value =  "value";
                value+=ix;
                message->setStringProperty("key", value);

                printf( "Sent message #%d from thread %s\n", ix+1, threadIdStr.c_str() );
                producer->send(message.get());
                Thread::sleep(1000);
            }

        }catch ( CMSException& e ) {
            e.printStackTrace();
        }
    }

private:

    void cleanup(){
        destination = nullptr;
        producer = nullptr;

        // Close open resources.
        try{
            if( session != nullptr ) session->close();
            if( connection != nullptr ) connection->close();
        }catch ( CMSException& e ) { e.printStackTrace(); }

        session = nullptr;
        connection = nullptr;
    }
};