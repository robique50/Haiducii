#include "routing.h"
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

	CROW_ROUTE(m_app, "/login").methods(crow::HTTPMethod::POST)([this, &db]
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

	CROW_ROUTE(m_app, "/joinLobby").methods("POST"_method)([&db, this](const crow::request& req) {
		auto jsonBody = crow::json::load(req.body);
		if (!jsonBody || !jsonBody.has("userID") || !jsonBody.has("lobbyCode")) {
			return crow::response(400, "Invalid request");
		}
		int userID = jsonBody["userID"].i();
		std::string lobbyCode = jsonBody["lobbyCode"].s();

		User newUser = db.getUserById(userID);
		if (newUser.getID() == -1) {
			return crow::response(400, "User not found");
		}

		Game lobby = db.getGameByCode(lobbyCode);
		if (lobby.GetId() == -1) {
			return crow::response(404, "Lobby not found");
		}

		if (!db.addPlayerToGame(newUser, lobbyCode)) {
			return crow::response(500, "Failed to join lobby");
		}

		crow::json::wvalue response;
		response["message"] = "Joined lobby successfully";
		return crow::response(200, response);
		});


	CROW_ROUTE(m_app, "/createLobby").methods("POST"_method)([&db, this](const crow::request& req) {
		auto jsonBody = crow::json::load(req.body);
		if (!jsonBody || !jsonBody.has("userID")) {
			return crow::response(400, "Invalid request");
		}
		int userID = jsonBody["userID"].i();

		auto code = Game::generateUniqueCode();

		User newUser = db.getUserById(userID);

		if (!db.addGame(newUser, code)) {
			return crow::response(500, "Failed to create game");
		}

		crow::json::wvalue response;
		response["roomCode"] = code;
		std::cout << "Generated room code: " << code << std::endl;

		return crow::response(200, response);
		});

	CROW_ROUTE(m_app, "/getLobbyInfo").methods("GET"_method)([&db](const crow::request& req) {
		std::string lobbyCode = req.url_params.get("lobbyCode");
		Game lobby = db.getGameByCode(lobbyCode);
		if (lobby.GetId() == -1) {
			return crow::response(404, "Lobby not found");
		}

		std::vector<std::string> playerNames = lobby.GetPlayerNames();

		crow::json::wvalue response;
		response["players"] = playerNames;
		return crow::response(200, response);
		});

	CROW_ROUTE(m_app, "/addChat").methods("GET"_method, "POST"_method)([&db](const crow::request& req) {
		auto x = crow::json::load(req.body);
		if (!x) return crow::response{ 400, "Invalid request" };

		std::string roomID = x["roomID"].s();
		std::string username = x["username"].s();
		std::string text = x["text"].s();

		auto gameOpt = db.getGame(roomID);
		if (!gameOpt) {
			return crow::response{ 404, "Game not found" };
		}

		auto roundOpt = db.getRound(roomID);
		std::string currentWord;
		if (roundOpt.has_value()) {
			currentWord = roundOpt->GetCurrentWord();
			std::transform(currentWord.begin(), currentWord.end(), currentWord.begin(), ::tolower);
		}

		std::string currentChat = gameOpt->getChat();
		std::transform(text.begin(), text.end(), text.begin(), ::tolower);

		currentChat += username + ": " + text + "\n";

		if (!db.setGameChat(roomID, currentChat))
			return crow::response{ 409, "Error adding the chat." };

		return crow::response{ 200 };
		});


	CROW_ROUTE(m_app, "/getChat").methods("POST"_method)([&](const crow::request& req) {
		auto x = crow::json::load(req.body);
		if (!x) return crow::response{ 400, "Invalid request" };

		std::string roomID = x["roomID"].s();

		auto gameOpt = db.getGame(roomID);
		if (!gameOpt) {
			return crow::response{ 404, "Game not found" };
		}

		std::string chat = gameOpt->getChat();

		return crow::response{ chat };
});

	m_app.port(18080).multithreaded().run();
}