#include "routing.h"
#include "words.h"
#include "bcrypt.h"
void skribbl::Routing::Run(skribbl::DataBase& db)
{
	CROW_ROUTE(m_app, "/")([]() {
		return "This is an example app of crow and sql-orm";
		});
    // Registration Route
    CROW_ROUTE(m_app, "/register").methods(crow::HTTPMethod::POST)([this,&db](const crow::request& req) {
        auto x = crow::json::load(req.body);
        if (!x) {
            return crow::response(400, "Invalid JSON");
        }

        std::string fullname = x["fullname"].s();
        std::string username = x["username"].s();
        std::string password = x["password"].s();


        User newUser(fullname, username, password);
        try {
            db.addUser(newUser);
            return crow::response(200, "User registered successfully");
        }
        catch (const std::exception& e) {
            // Handle specific exceptions if necessary
            return crow::response(500, "Error registering user: " + std::string(e.what()));
        }
        });

    // Login Route 
    CROW_ROUTE(m_app, "/login").methods(crow::HTTPMethod::POST)([&db](const crow::request& req) {
        auto x = crow::json::load(req.body);
        if (!x)
            return crow::response(400, "Invalid JSON");

        std::string username = x["username"].s();
        std::string password = x["password"].s();

        // Validate username and password
        // ...

        return crow::response(200, "Login successful");
        });

	m_app.port(18080).multithreaded().run();
}





