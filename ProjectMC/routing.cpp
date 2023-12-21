#include "routing.h"
#include  "words.h"
#include "PlayerManagement.h"
static const int numberOfWords = 16;

void skribbl::Routing::Run(skribbl::DataBase& db)
{

	CROW_ROUTE(m_app, "/")([]() {
		return "This is an example app of crow and sql-orm";
		});
	// Registration Route
	CROW_ROUTE(m_app, "/register").methods(crow::HTTPMethod::POST)([this, &db](const crow::request& req) {
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

			return crow::response(500, "Error registering user: " + std::string(e.what()));
		}
		});

	skribbl::PlayerManager playerManager;
	CROW_ROUTE(m_app, "/login").methods(crow::HTTPMethod::POST)([&db,&playerManager]
	(const crow::request& req) {
		auto x = crow::json::load(req.body);
		if (!x) {
			return crow::response(400, "Invalid JSON");
		}

		std::string username = x["username"].s();
		std::string password = x["password"].s();

		User user = db.getUserByUsername(username);
		if (user.isValid() && user.getPassword() == password) {
			int userID = user.getID();


			if (userID == -1) {
				return crow::response(401, "User not found");
			}

			playerManager.addPlayer(user);

			crow::json::wvalue response;
			response["message"] = "Login successful";
			response["userID"] = userID;
			response["username"] = username;

			return crow::response(200, response);
		}
		else {
			return crow::response(401, "Invalid username or password");
		}
		});
	
	CROW_ROUTE(m_app, "/getStatistics/<int>").methods(crow::HTTPMethod::GET)([&db](int userID) {
		User user = db.getUserById(userID);
		if (!user.isValid()) {
			return crow::response(404, "User not found");
		}

		Statistics stats = user.getStatistics();

		crow::json::wvalue response;
		response["userID"] = user.getID();
		response["username"] = user.getUsername();
		response["totalScore"] = stats.getTotalScore();
		response["averageScore"] = stats.getAverageScore();
		response["averageTime"] = stats.getAverageTime();
		response["gamesPlayed"] = stats.getGamesPlayed();

		return crow::response{ response };
		});

	CROW_ROUTE(m_app, "/getwords")([&db]() {
		std::vector<crow::json::wvalue> words_json;
		auto words = db.getRandomWords(numberOfWords);
		for (const auto& word : words)
		{
			words_json.push_back(crow::json::wvalue{
				{"id", word.getId()},
				{"word", word.getWord()}
				});
		}
		return crow::json::wvalue{ words_json };
		});

	CROW_ROUTE(m_app, "/getConnected").methods(crow::HTTPMethod::GET)([this,&playerManager]() {
		crow::json::wvalue response;

		const auto& allPlayers = playerManager.getPlayers();
		for (const auto& [id, player] : allPlayers) {
			response["players"][std::to_string(id)] = {
				{"name", player.getUsername()},
			};
		}

		return crow::response{ response };
		});

	m_app.port(18080).multithreaded().run();
}






