#include "server.h"
#include "Database.h"
import user;
void serverHandle()
{
	crow::SimpleApp app;
	useDatabase();
	CROW_ROUTE(app, "/")([]()
		{
			return "The server is running ";
		});

	CROW_ROUTE(app, "/register/<string>")
		([db&]
		() 	
		{
			using namespace sqlite_orm; // fara asta nu merg operatorii pt conditii (==, < etc)
			auto rows = db.select(sql::columns(&Word::word);
		);
		});

	
	app.port(18080).multithreaded().run();
}
