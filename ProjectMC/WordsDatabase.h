#pragma once
#include <string>
#include <vector>

#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

struct Words
{
	int id;
	std::string word;
};

inline auto makeWords(const std::string& filename)
{

    
    return sql::make_storage(filename,
        sql::make_table("Words",
            sql::make_column("id", &Words::id, sql::primary_key().autoincrement()),
            sql::make_column("words", &Words::word,sql::unique())));
}

using Storage = decltype(makeWords(""));


void populateStorage(Storage& storage);

