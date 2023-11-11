#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
import user;


namespace sql = sqlite_orm;
using skribbl;
struct Word
{
	int id;
	std::string word;
};



inline auto createStorage(const std::string& filename)
{

    
    return sql::make_storage(
        filename,
        sql::make_table(
            "Words",
            sql::make_column("id", &Word::id, sql::primary_key().autoincrement()),
            sql::make_column("word", &Word::word)
        ), 
        sql::make_table(
            "User",
            sql::make_column("id",&User::id::primary_key().autoincrement()),
            sql::make_column("username",&User::getUsername()),
            sql::make_column("password",&User::getPassword())
        )
    )
    );
}

using Storage = decltype(createStorage(""));

void populateStorage(Storage& storage);

