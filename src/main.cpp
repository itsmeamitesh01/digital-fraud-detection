#include <iostream>
#include <map>
#include <vector>
#include <conio.h>   // For _getch()
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

string getHiddenPassword() {
    string password = "";
    char ch;

    while (true) {
        ch = _getch();   // get character without showing it

        if (ch == 13) { // ENTER key
            cout << endl;
            break;
        }
        else if (ch == 8) { // BACKSPACE
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";  // erase a star
            }
        }
        else {
            password += ch;
            cout << "*";
        }
    }

    return password;
}


bool login(string& uid) {
    string id, pass;
    cout << "User ID: ";
    cin >> id;
    cout << "Password: ";
    pass = getHiddenPassword();


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

double getLast24HourSpent(const string& uid) {
    double sum = 0;
    time_t now = time(0);

    for (auto &tx : history[uid]) {
        // Only consider DEBIT transactions in last 24 hours (86400 seconds)
        if (tx.type == "DEBIT" && difftime(now, tx.timestamp) <= 86400) {
            sum += tx.amount;
        }
    }
    return sum;
}


void processTransaction(string uid) {
    double amt;
    string loc;

    cout << "Enter Amount: ";
    cin >> amt;

    if (amt <= 0) {
        cout << "Invalid Amount\n";
        return;
    }

    cout << "Enter Location: ";
    cin >> loc;
    loc = toUpperCase(loc);   // Case-insensitive normalization

    // ✅ DAILY TRANSACTION COMPLIANCE CHECK (₹1,00,000 / 24 hours)
    double spentToday = getLast24HourSpent(uid);

    if (spentToday + amt > 100000) {
        cout << "DAILY LIMIT EXCEEDED! You have already spent Rs. "
            << spentToday << " in the last 24 hours.\n";
        return;
    }

    // Proceed with DEBIT transaction
    Transaction tx(uid, amt, loc, "DEBIT");
    int risk = FraudEngine::calculateRisk(tx, history[uid]);


    cout << "Fraud Risk Score: " << risk << endl;

    if (risk >= 70) {
        users[uid].blocked = true;
        FileManager::saveUsers(users);

        cout << "\n!! FRAUD DETECTED - ACCOUNT BLOCKED !!\n";
        cout << "You have been logged out for security reasons.\n";

        exit(0);   // ✅ IMMEDIATE TERMINATION (FORCED LOGOUT)
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


void walletRecharge(string uid) {
    double amt;

    cout << "Enter Recharge Amount: ";
    cin >> amt;

    if (amt <= 0) {
        cout << "Invalid Recharge Amount\n";
        return;
    }

    // CREDIT transaction (trusted)
    Transaction tx(uid, amt, "INDIA", "CREDIT");

    users[uid].balance += amt;
    history[uid].push_back(tx);

    FileManager::saveUsers(users);
    FileManager::saveTransactions(history);

    cout << "Wallet Recharged Successfully\n";
}


void dashboard(string uid) {
    int choice;
    do {
        cout << "\n1. Balance\n2. Debit Transaction\n3. Wallet Recharge\n4. Logout\nChoice: ";

        cin >> choice;

        if (choice == 1)
            cout << "Balance: Rs. " << users[uid].balance << endl;
        else if (choice == 2)
            processTransaction(uid);   // DEBIT
        else if (choice == 3)
            walletRecharge(uid);       // CREDIT


    } while (choice != 4);
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
