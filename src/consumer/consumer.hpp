#pragma once
#include "../ActiveMq.hpp"
#include <string>
using namespace std;

class Consumer : public ExceptionListener,
                            public MessageListener,
                            public DefaultTransportListener {
private:

    Connection* connection;
    Session* session;
    Destination* destination;
    MessageConsumer* consumer;
    bool useTopic;
    std::string brokerURI;
    std::string destURI;
    bool clientAck;

private:

    Consumer(const Consumer&);
    Consumer& operator=(const Consumer&);

public:

    Consumer(const std::string& brokerURI,
                        const std::string& destURI,
                        bool useTopic = false,
                        bool clientAck = false) :
            connection(nullptr),
            session(nullptr),
            destination(nullptr),
            consumer(nullptr),
            useTopic(useTopic),
            brokerURI(brokerURI),
            destURI(destURI),
            clientAck(clientAck) {
    }

    virtual ~Consumer() {
        this->cleanup();
    }

    void close() {
        this->cleanup();
    }

    void runConsumer() {

        try {

            // Create a ConnectionFactory
//            ActiveMQConnectionFactory* connectionFactory = new ActiveMQConnectionFactory(ActiveMQConnectionFactory::DEFAULT_URI);
            ActiveMQConnectionFactory* connectionFactory = new ActiveMQConnectionFactory(brokerURI);

            // Create a Connection
            connection = connectionFactory->createConnection();
            delete connectionFactory;

            ActiveMQConnection* amqConnection = dynamic_cast<ActiveMQConnection*>(connection);
            if (amqConnection != NULL) {
                amqConnection->addTransportListener(this);
            }

            connection->start();

            connection->setExceptionListener(this);

            // Create a Session
            if (clientAck) {
                session = connection->createSession(Session::CLIENT_ACKNOWLEDGE);
            } else {
                session = connection->createSession(Session::AUTO_ACKNOWLEDGE);
            }

            // Create the destination (Topic or Queue)
//            if (useTopic) {
//                destination = session->createTopic(destURI);
//            } else {
                destination = session->createQueue(destURI);
//            }

            // Create a MessageConsumer from the Session to the Topic or Queue
            consumer = session->createConsumer(destination);
            consumer->setMessageListener(this);

        } catch (CMSException& e) {
            e.printStackTrace();
        }
    }

    // Called from the consumer since this class is a registered MessageListener.
    virtual void onMessage(const Message* message) {
        static int count = 0;

        try {
            count++;
            const TextMessage* textMessage = dynamic_cast<const TextMessage*>(message);
            string text = "";

            if (textMessage != nullptr) {
                text = textMessage->getText();
            } else {
                text = "NOT A TEXTMESSAGE!";
            }

            const cms::BytesMessage* d = dynamic_cast<const BytesMessage*>(message);

            if (clientAck) {
                message->acknowledge();
            }

            printf("Message #%d Received: %s\n", count, text.c_str());
        } catch (CMSException& e) {
            e.printStackTrace();
        }
    }

    // If something bad happens you see it here as this class is also been
    // registered as an ExceptionListener with the connection.
    virtual void onException(const CMSException& ex AMQCPP_UNUSED) {
        printf("CMS Exception occurred.  Shutting down client.\n");
        exit(1);
    }

    virtual void onException(const decaf::lang::Exception& ex) {
        printf("Transport Exception occurred: %s \n", ex.getMessage().c_str());
    }

    virtual void transportInterrupted() {
        std::cout << "The Connection's Transport has been Interrupted." << std::endl;
    }

    virtual void transportResumed() {
        std::cout << "The Connection's Transport has been Restored." << std::endl;
    }

private:

    void cleanup(){
        try{
            if( destination != nullptr ) delete destination;
        }catch (CMSException& e) {}
        destination = nullptr;

        try{
            if( consumer != nullptr ) delete consumer;
        }catch (CMSException& e) {}
        consumer = nullptr;

        // Close open resources.
        try{
            if( session != nullptr ) session->close();
            if( connection != nullptr ) connection->close();
        }catch (CMSException& e) {}

        // Now Destroy them
        try{
            if( session != nullptr ) delete session;
        }catch (CMSException& e) {}
        session = nullptr;

        try{
            if( connection != nullptr ) delete connection;
        }catch (CMSException& e) {}
        connection = nullptr;
    }
};

