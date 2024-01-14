﻿#include "Database.h"

import user;

namespace skribbl
{
	bool DataBase::Initialize()
	{
		m_db.sync_schema();
		auto initWordsCount = m_db.count<Words>();
		if (initWordsCount == 0)
		{
			populateStorage();
			std::cout << "Database populated succesfully" << std::endl;
		}
		auto wordsCount = m_db.count<Words>();
		return wordsCount != 0;

	}

	void DataBase::addUser(const User& user)
	{
		try {
			m_db.insert(user);
			std::cout << "User added succesfully" << std::endl;
		}
		catch (const std::exception& e) {
			std::cerr << "Error at adding user: " << e.what() << std::endl;
		}
	}

	void DataBase::addWord(const Words& word)
	{
		try {
			m_db.insert(word);
			std::cout << "Word added succesfully" << std::endl;
		}
		catch (const std::exception& e) {
			std::cerr << "Error at adding word: " << e.what() << std::endl;
		}

	}

	void DataBase::populateStorage() {
		std::vector<Words> words;
		std::ifstream f("listOfWords.txt");
		if (!f) {
			std::cerr << "Unable to open file." << std::endl;
			return;
		}
		for (std::string currentWord; f >> currentWord; ) {
			words.emplace_back(-1, std::move(currentWord));
		}
		m_db.insert_range(words.begin(), words.end());
	}

	int DataBase::getWordsCount()
	{
		int WordsCount = m_db.count<Words>();
		return WordsCount;
	}


	bool DataBase::userExists(const User& user)
	{
		auto allUsers = m_db.get_all<User>();
		return std::any_of(allUsers.begin(), allUsers.end(), [&user]
		(const auto& user1) {
				return user == user1;
			});
	}

	void DataBase::showUsers()
	{
		auto users = m_db.get_all<User>();
		std::ranges::for_each(users, [](const User& user) {
			std::cout << "ID: " << user.getID() << ", Username: "
				<< user.getUsername() << ", Password: " << user.getPassword() <<", Score:"<<user.GetPoints()<<std::endl;
			});
	}

	void DataBase::showWordsFromDatabase()
	{
		auto allWords = m_db.get_all<Words>();
		std::ranges::for_each(allWords, [](const Words& word) {
			std::cout << "ID: " << word.getId() << ", Word: " << word.getWord() << "\n";
			});
	}

	User DataBase::getUserByUsername(const std::string& username)
	{
		try {
			auto allUsers = m_db.get_all<User>();
			for (const auto& user : allUsers) {
				if (user.getUsername() == username) {
					return user;
				}
			}
		}
		catch (const std::exception& e) {
			std::cerr << "Error retrieving user '" << username << "': " << e.what() << std::endl;
		}
		return User(-1, "", "");
	}

	void DataBase::removeWord(const Words& word)
	{
		auto words = m_db.get_all<Words>();
		auto it = std::ranges::find_if(words, [&word](const auto& w) { return w.getId() == word.getId(); });
		if (it != words.end()) {
			m_db.remove<Words>(it->getId());
			std::cout << "Word removed successfully" << std::endl;
		}
		else {
			std::cout << "Word not found" << std::endl;
		}
	}

	void DataBase::removeUser(const User& user)
	{
		try {
			m_db.remove<User>(user.getID());
			std::cout << "User removed successfully" << std::endl;
		}
		catch (const std::exception& e) {
			std::cerr << "Error at removing user: " << e.what() << std::endl;
		}
	}

	User DataBase::getUserById(const int& id)
	{
		try {
			auto allUsers = m_db.get_all<User>();
			for (const auto& user : allUsers) {
				if (user.getID() == id) {
					return user;
				}
			}
		}
		catch (const std::exception& e) {
			std::cerr << "Error retrieving user '" << id << "': " << e.what() << std::endl;
		}
		return User(-1, "", "");
	}

	bool DataBase::addGame(const User& user, const std::string& gameCode) {
		try {
			Game newGame{ -1, user, gameCode, 1 };


			m_db.insert(newGame);


			Round newRound{ -1, gameCode };
			m_db.insert(newRound);

			return true;
		}
		catch (const std::exception& e) {
			std::cerr << "Exception occurred while adding game: " << e.what() << "\n";
			return false;
		}
	}

	int DataBase::addRound(const Round& round)
	{
		try {
			m_db.insert(round);
			return m_db.last_insert_rowid();
		}
		catch (const std::exception& e) {
			std::cerr << "Exception occurred while adding round: " << e.what() << "\n";
			return -1;
		}
	}

	Game DataBase::getGameByCode(const std::string& gameCode)
	{
		auto games = m_db.get_all<Game>();
		auto it = std::ranges::find_if(games, [&gameCode](const Game& game) {
			return game.GetGameCode() == gameCode;
			});
		return (it != games.end()) ? *it : Game();
	}

	bool DataBase::addPlayerToGame(const User& user, const std::string& gameCode) {
		try {
			auto games = m_db.get_all<Game>(sqlite_orm::where(sqlite_orm::c(&Game::GetGameCode) == gameCode));
			if (!games.empty()) {
				Game& game = games.front();
				auto existingPlayers = game.GetPlayers();
				bool playerExists = std::ranges::find_if(existingPlayers, [&user](const User& u) {
					return u.getID() == user.getID();
					}) != existingPlayers.end();

					if (!playerExists) {
						game.AddPlayer(user);

						std::string serializedPlayers = game.SerializePlayers();

						m_db.update_all(sqlite_orm::set(sqlite_orm::c(&Game::SerializePlayers) = serializedPlayers),
							sqlite_orm::where(sqlite_orm::c(&Game::GetId) == game.GetId()));

						return true;
					}
			}
		}
		catch (const std::exception& e) {
			std::cerr << "Exception occurred while adding player to game: " << e.what() << "\n";
		}
		return false;
	}

	bool DataBase::removePlayerFromGame(const User& user, const std::string& gameCode)
	{
		try
		{
			auto existingGames = m_db.get_all<Game>(
				sql::where(sql::c(&Game::GetGameCode) == gameCode)
			);

			if (existingGames.empty()) {
				std::cerr << "Game not found for room ID: " << gameCode<< "\n";
				return false;
			}

			auto& game = existingGames.front();
			game.RemovePlayer(user);

			m_db.update(game);
			return true;
		}
		catch (const std::exception& e) {
			std::cerr << "Exception occurred while removing player from game: " << e.what() << "\n";
			return false;
		}
	}

	Round DataBase::getRound(const std::string& gameCode)
	{
		auto existingRounds = m_db.get_all<Round>(
			sql::where(sql::c(&Round::GetGameId) == gameCode)
		);
		return existingRounds.front();
	}

	Game DataBase::getGame(const std::string& gameCode)
	{
		auto existingGames = m_db.get_all<Game>(
			sql::where(sql::c(&Game::GetGameCode) == gameCode)
		);
		return existingGames.front();
	}

	int DataBase::getPlayerScore(const std::string& username)
	{
		auto existingPlayers = m_db.get_all<User>(
			sql::where(sql::c(&User::getUsername) == username)
		);

		if (existingPlayers.empty())
			return 0;

		return existingPlayers.front().GetPoints();
	}

	bool DataBase::setGameChat(const std::string& gameCode, const std::string& chat)
	{
		try
		{
			auto games = m_db.get_all<Game>(
				sql::where(sql::c(&Game::GetGameCode) == gameCode)
			);

			if (games.empty())
				return false;

			auto& game = games[0];
			game.SetChat(chat);
			m_db.update(game);
			return true;
		}
		catch (const std::exception& exception) {
			std::cerr << "Exception occurred while setting game chat: " << exception.what() << "\n";
		}
		return false;
	}
	bool DataBase::setGameStatus(const std::string& gameCode, const int& status)
	{
		try
		{
			auto existingGames = m_db.get_all<Game>(
				sql::where(sql::c(&Game::GetGameCode) == gameCode)
			);

			if (existingGames.empty())
				return false;

			auto& game = existingGames.front();
			game.SetGameStatusInt(status);
			m_db.update(game);
			return true;
		}
		catch (const std::exception& e) {
			std::cerr << "Exception occurred while setting game status: " << e.what() << "\n";
			return false;
		}
	}

	void DataBase::setPlayerScore(const std::string& username, int score)
	{
		try
		{
			auto existingPlayers = m_db.get_all<User>(
				sql::where(sql::c(&User::getUsername) == username)
			);

			if (existingPlayers.empty())
				return;

			auto& player = existingPlayers.front();
			player.SetPoints(score);
			m_db.update(player);
		}
		catch (const std::exception& e) {
			std::cerr << "Exception occurred while setting player score: " << e.what() << "\n";
		}
		
	}

	int DataBase::generateRandomNumber(const int& min, const int& max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distribution(min, max);
		return distribution(gen);
	}
	std::string DataBase::getRandomWord()
	{
		auto wordCount = m_db.count<Words>();
		auto randomWordIndex = generateRandomNumber(1, wordCount);
		auto word = m_db.get<Words>(randomWordIndex);
		return word.getWord();
	}
}