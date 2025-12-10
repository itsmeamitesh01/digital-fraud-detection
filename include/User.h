#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
public:
    string userId;
    string password;
    double balance;
    bool blocked;

    User();
    User(string id, string pass);
};

#endif
