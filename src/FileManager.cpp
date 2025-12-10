#include "FileManager.h"
#include <fstream>

void FileManager::saveUsers(const map<string, User>& users) {
    ofstream file("data/users.dat");
    for (auto& u : users)
        file << u.second.userId << " "
             << u.second.password << " "
             << u.second.balance << " "
             << u.second.blocked << endl;
    file.close();
}

void FileManager::loadUsers(map<string, User>& users) {
    ifstream file("data/users.dat");
    if (!file) return;

    User u;
    while (file >> u.userId >> u.password >> u.balance >> u.blocked)
        users[u.userId] = u;
    file.close();
}

void FileManager::saveTransactions(
    const map<string, vector<Transaction>>& txs) {
    ofstream file("data/transactions.dat");
    for (auto& pair : txs)
        for (auto& t : pair.second)
            file << t.userId << " "
                 << t.amount << " "
                 << t.location << " "
                 << t.type << " "
                 << t.timestamp << endl;
    file.close();
}

void FileManager::loadTransactions(
    map<string, vector<Transaction>>& txs) {
    ifstream file("data/transactions.dat");
    if (!file) return;

    Transaction t;
    while (file >> t.userId >> t.amount
           >> t.location >> t.type >> t.timestamp)
        txs[t.userId].push_back(t);
    file.close();
}

