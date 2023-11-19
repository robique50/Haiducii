#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sqlite_orm/sqlite_orm.h>
#include <list>

#include "words.h"

import user;
using skribbl::User;

namespace sql = sqlite_orm;

class GameDatabase {
public:
    GameDatabase(const std::string& filename);
    void useDatabase();
    void populateStorage();
    void addUser(const User& user);
    void showWordsCount();
    bool userExists(const User& user);

    void addUser(const User& user);
    const std::list<User>& getUsersList();

private:
    sql::internal::storage_t<sqlite_orm::internal::columns_t<Words>> wordsTable;
    sql::internal::storage_t<sqlite_orm::internal::columns_t<User>> usersTable;

    std::list<User> usersList;
};