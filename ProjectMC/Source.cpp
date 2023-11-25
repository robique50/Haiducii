#include <filesystem>
#include <iostream>
#include <memory>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

#include "Database.h"
#include "routing.h"

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

	Routing r;
	r.Run(db);
	

    return 0;
}