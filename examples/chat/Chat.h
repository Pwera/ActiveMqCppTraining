#ifndef _EXAMPLE_TOPICS_CHAT_CHAT_H_
#define _EXAMPLE_TOPICS_CHAT_CHAT_H_

#include <memory>
#include "../ActiveMq.hpp"


    /**
     * Simple Chat Client that uses a Topic
     */
    class Chat : public cms::MessageListener,
                 public cms::ExceptionListener {
    private:

        std::unique_ptr<cms::Connection> connection;
        std::unique_ptr<cms::Session> session;
        std::unique_ptr<cms::MessageConsumer> consumer;
        std::unique_ptr<cms::MessageProducer> producer;
        std::unique_ptr<cms::Destination> topic;

        std::string brokerURI;
        std::string username;
        std::string password;
        std::string topicName;

    private:

        Chat( const Chat& );
        Chat& operator= ( const Chat& );

    public:

        static const char* DEFAULT_BROKER_URI;
        static const char* DEFAULT_TOPIC_NAME;

    public:

        Chat();
        virtual ~Chat();

        virtual void onMessage( const cms::Message* message );
        virtual void onException( const cms::CMSException& ex );

        /**
         * Sets the BrokerURI
         */
        void setBrokerURI( const std::string& uri ) {
            this->brokerURI = uri;
        }

        /**
         * Gets the BrokerURI
         */
        std::string getBrokerURI() const {
            return this->brokerURI;
        }

        /**
         * Sets the Topic Name
         */
        void setTopicName( const std::string& topicName ) {
            this->topicName = topicName;
        }

        /**
         * Gets the Topic Name
         */
        std::string getTopicName() const {
            return this->topicName;
        }

        /**
         * Sets the User Name
         */
        void setUsername( const std::string& username ) {
            this->username = username;
        }

        /**
         * Gets the User Name
         */
        std::string getUsername() const {
            return this->username;
        }

        /**
         * Sets the Password
         */
        void setPassword( const std::string& password ) {
            this->password = password;
        }

        /**
         * Gets the Password
         */
        std::string getPassword() const {
            return this->password;
        }

        /**
         * Run the Chat Application.
         */
        void run();

    };


#endif // _EXAMPLE_TOPICS_CHAT_CHAT_H_
