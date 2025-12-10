#include "FraudEngine.h"
#include <cmath>

int FraudEngine::calculateRisk(const Transaction& tx,
                               const vector<Transaction>& history) {
    int risk = 0;

    if (tx.amount > 50000)
        risk += 40;

    int recentTx = 0;
    for (auto& t : history)
        if (difftime(tx.timestamp, t.timestamp) <= 60)
            recentTx++;

    if (recentTx >= 3)
        risk += 30;

    if (tx.location != "INDIA")
        risk += 30;

    return risk;
}
