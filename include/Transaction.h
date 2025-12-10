#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>
using namespace std;

class Transaction {
public:
    string userId;
    double amount;
    string location;
    time_t timestamp;

    Transaction();
    Transaction(string uid, double amt, string loc);
};

#endif
