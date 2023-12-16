#include <filesystem>
#include <iostream>
#include <memory>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
#include <vector>
#include "Database.h"
#include "routing.h"
#include "Words.h"
#include "client.h"

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
	//std::string cuvant = "aloevera";
	//Round round{cuvant};
	std::cout << "\n";
	/*std::string cuvant = "aloevera";
	Round round{ cuvant };
	if(round.CorrectGuess("aloevera"))
		std::cout << "Corect\n";
	else
		std::cout << "Gresit\n";
	round.startRound(60);*/
	//r.Run(db);
	
	/*Client client("http://localhost:18080/getwords");
	std::unordered_set<std::string> words = client.getWordsFromServer();

	std::cout << "Words:\n";
	for (const auto& word : words) {
		std::cout << word << std::endl;
	}*/
	return 0;
}