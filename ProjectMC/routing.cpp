#include "routing.h"
#include "words.h"

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
        if (!x) {
            return crow::response(400, "Invalid JSON");
        }

        std::string username = x["username"].s();
        std::string password = x["password"].s();

        User user = db.getUserByUsername(username);
        if (user.isValid() && user.getPassword() == password) {
            return crow::response(200, "Login successful");
        }
        else {
            return crow::response(401, "Invalid username or password");
        }
	});

    CROW_ROUTE(m_app, "/getWords")([&db]() {
        std::vector<crow::json::wvalue> words_json;

        auto words = db.getRandomWords(16);
        for (const auto& word : words)
        {
            words_json.push_back(crow::json::wvalue{
                {"id", word.getId()}, 
                {"word", word.getWord()}
                });
        }
        return crow::json::wvalue{ words_json };
        });

	m_app.port(18080).multithreaded().run();
}   






