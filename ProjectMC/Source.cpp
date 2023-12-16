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
import round;

using namespace skribbl;
using skribbl::User;
using skribbl::Round;

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
	//r.Run(db);
	//std::string cuvant = "aloevera";
	//Round round{cuvant};
	std::cout << "\n";
	std::string cuvant = "aloevera";
	Round round{ cuvant };
	if(round.CorrectGuess("aloevera"))
		std::cout << "Corect\n";
	else
		std::cout << "Gresit\n";
	round.startRound(60);
	r.Run(db);
    return 0;
}