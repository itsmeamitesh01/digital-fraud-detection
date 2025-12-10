#include "Transaction.h"

Transaction::Transaction() {}

Transaction::Transaction(string uid, double amt, string loc) {
    userId = uid;
    amount = amt;
    location = loc;
    timestamp = time(0);
}
