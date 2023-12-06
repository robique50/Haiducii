#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
#include "words.h"
#include <algorithm>
#include <set>
#include <random>
namespace sql = sqlite_orm;

import user;

namespace skribbl
{
    inline auto createStorage(const std::string& filename)
    {
        return sql::make_storage(
            filename,
            sql::make_table(
                "Words",
                sql::make_column("id", &Words::setId, &Words::getId, sql::primary_key().autoincrement()),
                sql::make_column("word", &Words::setWord, &Words::getWord)
            ),
            sql::make_table(
                "User",
                sql::make_column("id",&User::setID, &User::getID, sql::primary_key().autoincrement()),
                sql::make_column("fullname", &User::setFullname, &User::getFullname),
                sql::make_column("username", &User::setUsername, &User::getUsername),
                sql::make_column("password", &User::setPassword, &User::getPassword)
            )
        );
    }

    using Storage = decltype(createStorage(""));

    class DataBase
    {
    public:
        bool Initialize();

        void addUser(const User& user);
        
        void addWord(const Words& word);

        void populateStorage();

        int getWordsCount();

        bool userExists(User user);

        void showUsers();

        void showWordsFromDatabase();

        std::vector<Words> getRandomWords(const int& numberOfWords);

        User getUserByUsername(const std::string& username);

        void removeWord(const Words& word);

        void removeUser(const User& user);

        void showUsersWithScoreGreaterThan(int score);
        
    private:
        const std::string db_file = "cuvinte.sqlite";
    private:
        Storage m_db = createStorage(db_file);
    };

}