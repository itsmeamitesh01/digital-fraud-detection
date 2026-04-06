#include "FileManager.h"
#include <fstream>
#include <sstream>

// XOR key for basic password obfuscation
// Not cryptographic - but prevents plaintext passwords in .dat files
static const uint8_t XOR_KEY = 0x5A;

string obfuscate(const string& password) {
    ostringstream oss;
    for (size_t i = 0; i < password.size(); i++) {
        if (i > 0) oss << "-";
        oss << (int)((uint8_t)password[i] ^ XOR_KEY);
    }
    return oss.str();
}

string deobfuscate(const string& encoded) {
    istringstream iss(encoded);
    string token;
    string result = "";
    while (getline(iss, token, '-')) {
        result += (char)(stoi(token) ^ XOR_KEY);
    }
    return result;
}

void FileManager::saveUsers(const map<string, User>& users) {
    ofstream file("data/users.dat");
    for (auto& u : users)
        file << u.second.userId << " "
             << obfuscate(u.second.password) << " "
             << u.second.balance << " "
             << u.second.blocked << endl;
    file.close();
}

void FileManager::loadUsers(map<string, User>& users) {
    ifstream file("data/users.dat");
    if (!file) return;

    User u;
    string encodedPass;
    while (file >> u.userId >> encodedPass >> u.balance >> u.blocked) {
        u.password = deobfuscate(encodedPass);
        users[u.userId] = u;
    }
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