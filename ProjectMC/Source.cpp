import user;
#include <filesystem>
#include <iostream>
#include <memory>

#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

#include "WordsDatabase.h"


int main()
{
	const std::string db_file = "words.sqlite";
	Storage db = createStorage(db_file);
	db.sync_schema();
	auto initWordsCount = db.count<Word>();
	if (initWordsCount == 0)
		populateStorage(db);
	auto WordsCount = db.count<Word>();
	std::cout << "wordsCount = " << WordsCount << '\n';
	User newUser("Adrian", "password");
	//addUser(db,newUser);
	auto UsersCount = db.count<User>();
	try {
		//addUser(db, newUser);
		auto UsersCount = db.count<User>();
		std::cout << "usersCount = " << UsersCount << '\n';
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
    return 0;
}