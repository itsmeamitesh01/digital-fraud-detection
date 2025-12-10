#include "Transaction.h"

Transaction::Transaction() {}

Transaction::Transaction(string uid, double amt, string loc, string t) {
    userId = uid;
    amount = amt;
    location = loc;
    type = t;
    timestamp = time(0);
}
