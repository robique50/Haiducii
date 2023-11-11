import user;
#include <filesystem>
#include <iostream>
#include <memory>

#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

#include "WordsDatabase.h"

namespace sql = sqlite_orm;

int main()
{
	const std::string db_file = "words.sqlite";
	Storage db = createStorage(db_file);
	db.sync_schema();
	auto initWordsCount = db.count<Words>();
	if (initWordsCount == 0)
		populateStorage(db);
	auto WordsCount = db.count<Words>();
	std::cout << "wordsCount = " << WordsCount << '\n';

    return 0;

}