#include <filesystem>
#include <iostream>
#include <memory>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
#include <vector>
#include "Database.h"
#include "routing.h"
#include "Words.h"
namespace sql = sqlite_orm;

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
	db.showUsers();
	Routing r;
	r.Run(db);
    return 0;
}