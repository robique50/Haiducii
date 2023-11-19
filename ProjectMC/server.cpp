#include "server.h"

void serverHandle()
{
	crow::SimpleApp app;

	CROW_ROUTE(app, "/")([]()
		{
			return "The server is running ";
		});
	app.port(18080).multithreaded().run();
}
