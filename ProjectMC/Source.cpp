#include <filesystem>
#include <iostream>
#include <memory>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
#include <vector>
#include "Database.h"
#include "routing.h"
#include "Words.h"
#include "../ProiectDLL/Score.h"

namespace sql = sqlite_orm;

import user;
import round;

using namespace skribbl;
using skribbl::User;
using skribbl::Round;

int main()
{
	DataBase db;
	Score::addScore();
	
	if (!db.Initialize())
	{
		std::cout << "Error: Database not found" << std::endl;
		return -1;
	}
	db.showUsers();
	Routing r;
	std::cout << "\n";
	r.Run(db);
	return 0;
}