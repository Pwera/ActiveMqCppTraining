#pragma once

#include "../ActiveMq.hpp"
#include <string>

using namespace std;

class Consumer : public ExceptionListener,
                 public MessageListener,
                 public DefaultTransportListener {
private:

    unique_ptr<Connection> connection;
    unique_ptr<Session> session;
    unique_ptr<Destination> destination;
    unique_ptr<MessageConsumer> consumer;
    bool useTopic;
    std::string brokerURI;
    std::string destURI;
    bool clientAck;

private:

    Consumer(const Consumer &);

    Consumer &operator=(const Consumer &);

public:

    Consumer(const std::string &brokerURI,
             const std::string &destURI,
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
            unique_ptr<ActiveMQConnectionFactory> connectionFactory(new ActiveMQConnectionFactory(brokerURI));

            // Create a Connection
            connection.reset(connectionFactory->createConnection());

            ActiveMQConnection *amqConnection = dynamic_cast<ActiveMQConnection *>(connection.get());
            amqConnection->addTransportListener(this);

            connection->start();

            connection->setExceptionListener(this);

            // Create a Session
            session.reset(connection->createSession(clientAck ? Session::CLIENT_ACKNOWLEDGE : Session::AUTO_ACKNOWLEDGE));

//             Create the destination (Topic or Queue)
            if (useTopic) {
                destination.reset(session->createTopic(destURI));
            } else {
                destination.reset( session->createQueue(destURI));
            }

            // Create a MessageConsumer from the Session to the Topic or Queue
            consumer.reset(session->createConsumer(destination.get()));
            consumer->setMessageListener(this);

        } catch (CMSException &e) {
            e.printStackTrace();
        }
    }

    // Called from the consumer since this class is a registered MessageListener.
    virtual void onMessage(const Message *message) {
        static int count = 0;

        try {
            count++;
            const TextMessage *textMessage = dynamic_cast<const TextMessage *>(message);

            string text = (textMessage != nullptr) ? textMessage->getText() : "NOT A TEXTMESSAGE!";
            const auto &key = textMessage->getStringProperty("key");

            const cms::BytesMessage *bytesMessage = dynamic_cast<const BytesMessage *>(message);

            if (bytesMessage != nullptr) {
                bytesMessage->getBodyLength();
            }

            if (clientAck) {
                message->acknowledge();
            }

            printf("Message %d bytesMessage Received: %s\n", count, text.c_str());
        } catch (CMSException &e) {
            e.printStackTrace();
        }
    }

    // If something bad happens you see it here as this class is also been
    // registered as an ExceptionListener with the connection.
    virtual void onException(const CMSException &ex AMQCPP_UNUSED) {
        printf("CMS Exception occurred.  Shutting down client.\n");
        exit(1);
    }

    virtual void onException(const decaf::lang::Exception &ex) {
        printf("Transport Exception occurred: %s \n", ex.getMessage().c_str());
    }

    virtual void transportInterrupted() {
        std::cout << "The Connection's Transport has been Interrupted." << std::endl;
    }

    virtual void transportResumed() {
        std::cout << "The Connection's Transport has been Restored." << std::endl;
    }

private:

    void cleanup() {
        destination = nullptr;
        consumer = nullptr;

        try {
            if (session != nullptr) session->close();
            if (connection != nullptr) connection->close();
        } catch (CMSException &e) {}


        session = nullptr;
        connection = nullptr;
    }
};

