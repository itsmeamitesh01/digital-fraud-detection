#include "User.h"

User::User() {}

User::User(string id, string pass) {
    userId = id;
    password = pass;
    balance = 100000;
    blocked = false;
}
