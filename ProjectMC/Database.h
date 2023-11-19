#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
#include "words.h"
import user;

namespace sql = sqlite_orm;
using namespace skribbl;

inline auto createStorage(const std::string& filename)
{
    return sql::make_storage(
        filename,
        sql::make_table(
            "Words",
            sql::make_column("id", &Words::getId, &Words::setId,sql::primary_key().autoincrement()),
            sql::make_column("word", &Words::getWord, &Words::setWord,sql::unique())
        ), 
        sql::make_table(
            "User",
            sql::make_column("id",
                &User::getID,
                &User::setID, sql::primary_key().autoincrement()),
            sql::make_column("username",&User::getUsername,&User::setUsername, sql::unique()),
            sql::make_column("password",&User::getPassword,&User::setPassword, sql::unique())
        )
    );
}

using Storage = decltype(createStorage(""));

void addUser(const User& user);

void populateStorage();

void useDatabase();

void showWordsCount();

bool userExists(User user);