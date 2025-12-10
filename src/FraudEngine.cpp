#include "FraudEngine.h"
#include <cmath>

int FraudEngine::calculateRisk(const Transaction& tx,
                               const vector<Transaction>& history) {
    // ✅ Credits are always safe
    if (tx.type == "CREDIT")
        return 0;

    int risk = 0;

    // High amount spike
    if (tx.amount > 50000)
        risk += 40;

    // Rapid transaction burst
    int recentTx = 0;
    for (auto& t : history)
        if (difftime(tx.timestamp, t.timestamp) <= 60 && t.type == "DEBIT")
            recentTx++;

    if (recentTx >= 3)
        risk += 30;

    // Geo mismatch
    if (tx.location != "INDIA")
        risk += 30;

    return risk;
}
