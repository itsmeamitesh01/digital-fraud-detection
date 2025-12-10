#include <iostream>
#include <map>
#include <vector>
#include <cctype>

using namespace std;

#include "../include/User.h"
#include "../include/Transaction.h"
#include "../include/FraudEngine.h"
#include "../include/FileManager.h"

map<string, User> users;
map<string, vector<Transaction>> history;

void createUser() {
    string id, pass;
    cout << "Enter User ID: ";
    cin >> id;
    cout << "Enter Password: ";
    cin >> pass;

    users[id] = User(id, pass);
    FileManager::saveUsers(users);

    cout << "Account Created Successfully\n";
}

bool login(string& uid) {
    string id, pass;
    cout << "User ID: ";
    cin >> id;
    cout << "Password: ";
    cin >> pass;

    if (users.count(id) && users[id].password == pass) {
        if (users[id].blocked) {
            cout << "Account Blocked Due To Fraud!\n";
            return false;
        }
        uid = id;
        return true;
    }
    cout << "Invalid Login\n";
    return false;
}

string toUpperCase(string s) {
    for (char &c : s)
        c = toupper(c);
    return s;
}

void processTransaction(string uid) {
    double amt;
    string loc;

    cout << "Enter Amount: ";
    cin >> amt;
    
    cout << "Enter Location: ";
    cin >> loc;
    loc = toUpperCase(loc);   // ✅ Normalized


    Transaction tx(uid, amt, loc);
    int risk = FraudEngine::calculateRisk(tx, history[uid]);

    cout << "Fraud Risk Score: " << risk << endl;

    if (risk >= 70) {
        users[uid].blocked = true;
        FileManager::saveUsers(users);
        cout << "🚨 FRAUD DETECTED - ACCOUNT BLOCKED 🚨\n";
        return;
    }

    if (users[uid].balance >= amt) {
        users[uid].balance -= amt;
        history[uid].push_back(tx);
        FileManager::saveUsers(users);
        FileManager::saveTransactions(history);
        cout << "Transaction Successful\n";
    } else {
        cout << "Insufficient Balance\n";
    }
}

void dashboard(string uid) {
    int choice;
    do {
        cout << "\n1. Balance\n2. New Transaction\n3. Logout\nChoice: ";
        cin >> choice;

        if (choice == 1)
            cout << "Balance: Rs." << users[uid].balance << endl;
        else if (choice == 2)
            processTransaction(uid);

    } while (choice != 3);
}

int main() {
    FileManager::loadUsers(users);
    FileManager::loadTransactions(history);

    int choice;
    string uid;

    do {
        cout << "\n1. Create Account\n2. Login\n3. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1)
            createUser();
        else if (choice == 2)
            if (login(uid))
                dashboard(uid);

    } while (choice != 3);

    return 0;
}
