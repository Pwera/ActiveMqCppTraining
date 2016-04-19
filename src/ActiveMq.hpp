#ifndef ACTIVEMQTRAINING_ACTIVEMQFILES_HPP
#define ACTIVEMQTRAINING_ACTIVEMQFILES_HPP


#include <decaf/util/concurrent/locks/ReentrantReadWriteLock.h>
#include <decaf/lang/Runnable.h>
#include <decaf/lang/Thread.h>
#include <decaf/lang/Math.h>
#include <decaf/lang/exceptions/InterruptedException.h>
#include <activemq/library/ActiveMQCPP.h>
#include <decaf/util/concurrent/locks/ReentrantReadWriteLock.h>
#include <decaf/util/concurrent/locks/ReentrantLock.h>
#include <decaf/lang/Runnable.h>
#include <cms/Connection.h>
#include <cms/Session.h>
#include <cms/MessageConsumer.h>
#include <cms/MessageListener.h>
#include <cms/Destination.h>
#include <cms/ExceptionListener.h>
#include <cms/CMSException.h>
#include <cms/CMSException.h>
#include <cms/ConnectionFactory.h>
#include <decaf/nio/ByteBuffer.h>
#include <decaf/nio/CharBuffer.h>
#include <decaf/nio/DoubleBuffer.h>
#include <decaf/nio/FloatBuffer.h>
#include <decaf/nio/LongBuffer.h>
#include <decaf/nio/IntBuffer.h>
#include <decaf/nio/ShortBuffer.h>
#include <decaf/internal/util/concurrent/TransferQueue.h>
#include <decaf/util/concurrent/Mutex.h>
#include <decaf/lang/System.h>
#include <decaf/util/ArrayList.h>
#include <decaf/util/Random.h>
#include <decaf/lang/exceptions/InterruptedException.h>
#include <decaf/lang/exceptions/RuntimeException.h>

using namespace decaf::util::concurrent::locks;
using namespace decaf::util::concurrent;
using namespace decaf::util::comparators;
using namespace decaf::util;
using namespace decaf::lang::exceptions;
using namespace decaf::lang;
using namespace decaf::internal::util::concurrent;
using namespace decaf::internal::util;
using namespace decaf::internal;
using namespace decaf::nio;
using namespace decaf;
using namespace activemq::library;
using namespace activemq;
using namespace cms;

class ActiveMqInit{

public:
    ActiveMqInit() {
        activemq::library::ActiveMQCPP::initializeLibrary();
    }

    virtual ~ActiveMqInit() {  activemq::library::ActiveMQCPP::shutdownLibrary();}
};
#endif //ACTIVEMQTRAINING_ACTIVEMQFILES_HPP
