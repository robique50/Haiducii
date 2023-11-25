#include "routing.h"

void skribbl::Routing::Run(skribbl::DataBase& db)
{
	CROW_ROUTE(m_app, "/")([]() {
		return "This is an example app of crow and sql-orm";
		});
    // Registration Route
    CROW_ROUTE(m_app, "/register").methods(crow::HTTPMethod::POST)([&db](const crow::request& req) {
        auto x = crow::json::load(req.body);
        if (!x)
            return crow::response(400, "Invalid JSON");

        std::string fullname = x["fullname"].s();
        std::string username = x["username"].s();
        std::string password = x["password"].s(); // Consider hashing the password

        User newUser(fullname, username, password);
        db.AddUser(newUser); // Method to add user to database

        return crow::response(200, "User registered successfully");
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

cpr::Response skribbl::Routing::getRandomWords(skribbl::DataBase& db, int numberOfWords)
{
    auto words = db.getRandomWords(numberOfWords);

    std::vector<crow::json::wvalue> jsonWords;
    for (const auto& word : words) {
        jsonWords.push_back({ {"id", word.getId()}, {"word", word.getWord()} });
    }

    return cpr::Response{ crow::json::dump(jsonWords), 200, {"Content-Type", "application/json"} };
}

