import user;
#include <filesystem>
#include <iostream>
#include <memory>

#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

#include "Database.h"
#include "server.h"

int main()
{
	
	useDatabase();
	showWordsCount();
	/*
	User newUser("Adrian", "password");
	//addUser(db,newUser);
	auto UsersCount = db.count<User>();
	try {
		addUser(db, newUser);
		auto UsersCount = db.count<User>();
		std::cout << "usersCount = " << UsersCount << '\n';
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	serverHandle();
	*/

    return 0;
}