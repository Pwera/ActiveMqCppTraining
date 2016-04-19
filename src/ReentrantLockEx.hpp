#ifndef ACTIVEMQTRAINING_REENTRANTLOCK_HPP
#define ACTIVEMQTRAINING_REENTRANTLOCK_HPP

#include <iostream>
#include <string>
#include <thread>
#include "ActiveMq.hpp"

using namespace std;
class Account {
    int balance = 500;
public:

    void debit(int amount) {
        balance = balance - amount;
    }

    void credit(int amount) {
        balance = balance + amount;
    }

    int getBalance() {
        return balance;
    }
};
class ATM : public Runnable {
Account *account = new Account();
decaf::util::concurrent::locks::Lock *lock = new decaf::util::concurrent::locks::ReentrantLock();
public:
    virtual void run() {

    for (int i = 0; i <10; i++) {
        lock->lock();
        if (account->getBalance() > 0) {
            makeWithdrawal(100);
        } else {
            cout<<"Not enough in amount for " << Thread::currentThread()->getName() << " to withdraw \n";
        }
        lock->unlock();
    }
}

private:
    void makeWithdrawal(int amt) {

    if (account->getBalance() >= amt) {
        cout<<Thread::currentThread()->getName()<< " cheked balance and the balance is :"
                           << account->getBalance();

        account->debit(amt);
        cout<<Thread::currentThread()->getName()<<
                 " completes the withdrawal and the balance: "
                           << account->getBalance();
    }
}

};

class ReentrantLockEx{

public:
    void start() {
        Runnable *atm = new ATM();
        Thread *withdrwer1 = new Thread(atm);
        withdrwer1->setName("withdrawer1");
        withdrwer1->start();

        Thread *withdrwer2 = new Thread(atm);
        withdrwer2->setName("withdrawer2");
        withdrwer2->start();
    }

};
#endif //ACTIVEMQTRAINING_REENTRANTLOCK_HPP
