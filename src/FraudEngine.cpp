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
    // Note: tx is not yet in history when this runs, so current tx counts as +1
    // Threshold is 2 (history) + 1 (current tx) = 3 total debits in 60 seconds
    int recentTx = 0;
    for (auto& t : history)
        if (difftime(tx.timestamp, t.timestamp) <= 60 && t.type == "DEBIT")
            recentTx++;

    if (recentTx >= 2)
        risk += 30;

    // Geo mismatch
    if (tx.location != "INDIA")
        risk += 30;

    return risk;
}