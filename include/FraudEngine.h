#ifndef FRAUD_ENGINE_H
#define FRAUD_ENGINE_H

#include <vector>
#include "Transaction.h"
using namespace std;

class FraudEngine {
public:
    static int calculateRisk(const Transaction& tx,
                             const vector<Transaction>& history);
};

#endif
