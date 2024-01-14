﻿#include "routing.h"
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


	CROW_ROUTE(m_app, "/getWord")([&db]() {
		return crow::response{ db.getRandomWord() };
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
		if (!x) {
			return crow::response{ 400, "Invalid request" };
		}
		std::string roomID = x["roomID"].s();
		std::string username = x["username"].s();
		std::string text = x["text"].s();

		std::string currentChat = db.getGame(roomID).GetChat();
		std::string currentWord = db.getRound(roomID).GetCurrentWord();
		std::transform(text.begin(), text.end(), text.begin(), ::tolower);
		std::transform(currentWord.begin(), currentWord.end(), currentWord.begin(), ::tolower);

		currentChat += username + ": " + text + "\n";

		if (!db.setGameChat(roomID, currentChat))
			return crow::response{ 409, "Error adding the chat." };

		return crow::response{ 200 };
		});


	CROW_ROUTE(m_app, "/getChat").methods("GET"_method, "POST"_method)([&](const crow::request& req) {
		auto x = crow::json::load(req.body);
		if (!x) {
			return crow::response{ 400, "Invalid request" };
		}
		std::string roomID = x["roomID"].s();
		std::string chat = db.getGame(roomID).GetChat();

		return crow::response{ chat };
		});

	CROW_ROUTE(m_app, "/clearChat").methods("POST"_method)([&db](const crow::request& req) {
		auto x = crow::json::load(req.body);
		if (!x) return crow::response{ 400, "Invalid request" };

		std::string roomID = x["roomID"].s();

		auto game = db.getGame(roomID);
		if (game.GetId() < 0)
		{
			return crow::response{ 404, "Game not found" };
		}

		if (!db.setGameChat(roomID, "Welcome to skribbl!")) {
			return crow::response{ 409, "Error clearing the chat." };
		}

		return crow::response{ 200 };
		});

	CROW_ROUTE(m_app, "/leaveRoom")
		.methods("GET"_method, "POST"_method)([&db](const crow::request& req) {
		auto x = crow::json::load(req.body);

		if (!x || !x.has("roomID") || !x.has("username")) {
			return crow::response(400, "Invalid request data.");
		}

		std::string roomID = x["roomID"].s();
		std::string username = x["username"].s();

		//std::transform(username.begin(), username.end(), username.begin(), ::tolower);
		auto player = db.getUserByUsername(username);


		if (player.getID() == -1) {
			return crow::response(404, "User not found.");
		}

		if (!db.removePlayerFromGame(player, roomID)) {
			return crow::response(409, "Error leaving the game.");
		}

		return crow::response(200, "Successfully left the game.");
			});


	CROW_ROUTE(m_app, "/gameStarted")
		.methods("GET"_method, "POST"_method)([&db](const crow::request& req) {
		auto x = crow::json::load(req.body);

		
		if (!x || !x.has("roomID")) {
			return crow::response(400, "Invalid request data.");
		}

		std::string roomID = x["roomID"].s();

	
		Game game = db.getGame(roomID);

		
		if (game.GetId() == -1) { 
			return crow::response(404, "Game not found.");
		}

		if (game.GetGameStatusAsInt() == 2) {
			return crow::response(200, "Game has started.");
		}

		return crow::response(409, "Game has not started yet.");
			});

	CROW_ROUTE(m_app, "/startGame")
		.methods("GET"_method, "POST"_method)([&db](const crow::request& req) {
		auto x = crow::json::load(req.body);

		if (!x || !x.has("roomID")) {
			return crow::response(400, "Invalid request data.");
		}

		std::string roomID = x["roomID"].s();

		Game currentGame = db.getGame(roomID);

		
		if (currentGame.GetId() == -1) { 
			return crow::response(404, "Game not found.");
		}

		std::vector<User> users = currentGame.GetPlayers();


		for (auto& user : users) {
			db.setPlayerScore(user.getUsername(), 0);
		}

		Round currentRound = db.getRound(roomID);
		int noOfWords = users.size() * currentGame.GetNoOfRounds(); 

		std::set<std::string> words;
		while (words.size() < noOfWords) {
			words.insert(db.getRandomWord());
		}

		
		currentRound.SetCurrentWord(*words.begin());
		words.erase(words.begin());
		currentRound.SetWords(words);
		currentRound.SetRoundNumber(1);
		currentRound.SetDrawingPlayer(users[0].getUsername());
		db.Update(currentRound);

		
		if (!db.setGameStatus(roomID, 2)) {
			return crow::response(409, "Error starting the game.");
		}

		return crow::response(200, "Game started successfully.");
			});

	CROW_ROUTE(m_app, "/playerScore")
		.methods("GET"_method)([&](const crow::request& req) {
		auto x = crow::json::load(req.body);
		std::string username = x["username"].s();
		std::string roomID = x["roomID"].s();

		//std::transform(username.begin(), username.end(), username.begin(), ::tolower);
		std::string score = std::to_string(db.getPlayerScore(username));

		return crow::response{ score };
			});

	CROW_ROUTE(m_app, "/currentNumberOfPlayers")
		.methods("GET"_method, "POST"_method)([&](const crow::request& req) {
		auto x = crow::json::load(req.body);
		std::string roomID = x["roomID"].s();

		std::string currentNumberOfPlayers = std::to_string(db.getGame(roomID).GetCurrentPlayers());

		return crow::response{ currentNumberOfPlayers };
			});



	m_app.port(18080).multithreaded().run();
}