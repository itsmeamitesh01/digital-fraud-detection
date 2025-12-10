#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <map>
#include <vector>
#include "User.h"
#include "Transaction.h"
using namespace std;

class FileManager {
public:
    static void saveUsers(const map<string, User>& users);
    static void loadUsers(map<string, User>& users);

    static void saveTransactions(const map<string,
                               vector<Transaction>>& txs);
    static void loadTransactions(map<string,
                               vector<Transaction>>& txs);
};

#endif
