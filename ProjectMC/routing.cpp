#include "routing.h"

void skribbl::Routing::Run(skribbl::DataBase& db)
{
	CROW_ROUTE(m_app, "/")([]() {
		return "This is an example app of crow and sql-orm";
		});

	m_app.port(18080).multithreaded().run();
}
