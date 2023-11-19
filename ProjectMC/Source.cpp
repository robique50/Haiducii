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
	
	User newUser("Adrian", "password");
	addUser(newUser);
	User newUser2("Adi", "passwrd");
	addUser(newUser2);
	User userTest("Adr", "pard");
	std::cout << userExists(userTest)<<"\n";
	
	

	serverHandle();
	

    return 0;
}