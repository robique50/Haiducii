#include <filesystem>
#include <iostream>
#include <memory>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
#include <vector>
namespace sql = sqlite_orm;

#include "Database.h"
#include "routing.h"
#include "Words.h"

import user;

using namespace skribbl;
using skribbl::User;

int main()
{
	DataBase db;
	if (!db.Initialize())
	{
		std::cout << "Error: Database not found" << std::endl;
		return -1;

	}
	std::vector < Words >words= db.getRandomWords(4);
	for (auto word : words) {
		std::cout << "Word ID: " << word.getId() << ", Word: " << word.getWord() << std::endl;
	}
	Routing r;
	r.Run(db);
	

    return 0;
}