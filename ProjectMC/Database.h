#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
#include "words.h"
import user;

using skribbl::User;

namespace sql = sqlite_orm;

namespace skribbl
{
    inline auto createStorage(const std::string& filename)
    {
        return sql::make_storage(
            filename,
            sql::make_table(
                "Words",
                sql::make_column("id", &Words::setId, &Words::getId, sql::primary_key().autoincrement()),
                sql::make_column("word", &Words::setWord, &Words::getWord, sql::unique())
            ),
            sql::make_table(
                "User",
                sql::make_column("id", &User::setID, &User::getID, sql::primary_key().autoincrement()),
                sql::make_column("username", &User::setUsername, &User::getUsername, sql::unique()),
                sql::make_column("password", &User::setPassword, &User::getPassword, sql::unique())
            )
        );
    }

    using Storage = decltype(createStorage(""));

    class DataBase
    {
    public:
        void addUser(const User& user);

        void populateStorage();

        void useDatabase();

        int getWordsCount();

        bool userExists(User user);

        void showUsers();

        void showWordsFromDatabase();
    private:
        const std::string db_file = "words.sqlite";
    private:
        Storage db = createStorage(db_file);
    };

}