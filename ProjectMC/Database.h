#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
#include "words.h"
#include <algorithm>
#include <set>
#include <random>
#include <iostream>
#include <cstdlib>
#include <ctime>
namespace sql = sqlite_orm;

import user;
import round;
import game;

namespace skribbl
{
	inline auto createStorage(const std::string& filename)
	{
		return sql::make_storage(
			filename,
			sql::make_table(
				"Words",
				sql::make_column("id", &Words::setId, &Words::getId, sql::primary_key().autoincrement()),
				sql::make_column("word", &Words::setWord, &Words::getWord)
			),
			sql::make_table(
				"User",
				sql::make_column("id", &User::setID, &User::getID, sql::primary_key().autoincrement()),
				sql::make_column("fullname", &User::setFullname, &User::getFullname),
				sql::make_column("username", &User::setUsername, &User::getUsername),
				sql::make_column("password", &User::setPassword, &User::getPassword)
			),
			sql::make_table(
				"Rounds",
				sql::make_column("id", &Round::SetId, &Round::GetId, sql::primary_key().autoincrement()),
				sql::make_column("gameid", &Round::SetGameId, &Round::GetGameId),
				sql::make_column("word", &Round::SetCurrentWord, &Round::GetCurrentWord),
				sql::make_column("drawingplayer", &Round::SetDrawingPlayer, &Round::GetDrawingPlayer),
				sql::make_column("roundnumber", &Round::SetRoundNumber, &Round::GetRoundNumber),
				sql::make_column("words", &Round::SerializeWords, &Round::DeserializeWords),
				sql::make_column("timeleft", &Round::SetTimeLeft, &Round::GetTimeLeft)
			),
			sql::make_table(
				"Games",
				sql::make_column("id", &Game::SetId, &Game::GetId, sql::primary_key().autoincrement()),
				sql::make_column("players", &Game::SerializePlayers, &Game::DeserializePlayers),
				sql::make_column("gamecode", &Game::SetGameCode, &Game::GetGameCode),
				sql::make_column("currentplayers", &Game::SetCurrentPlayers, &Game::GetCurrentPlayers),
				sql::make_column("status", &Game::SetGameStatusInt, &Game::GetGameStatusAsInt),
				sql::make_column("chat", &Game::SetChat, &Game::GetChat)
				
			)
		);
	}

	using Storage = decltype(createStorage(""));

	class DataBase
	{
	public:
		bool Initialize();

		void addUser(const User& user);

		void addWord(const Words& word);

		void populateStorage();

		int getWordsCount();

		bool userExists(const User& user);

		void showUsers();

		void showWordsFromDatabase();

		const std::vector<Words>& getRandomWords(const int& numberOfWords);

		User getUserByUsername(const std::string& username);

		void removeWord(const Words& word);

		void removeUser(const User& user);

		User getUserById(const int& id);

		bool addGame(const User& user, const std::string& gameCode);

		int addRound(const Round& round);

		Game getGameByCode(const std::string& gameCode);

		bool addPlayerToGame(const User& user, const std::string& gameCode);

	private:
		const std::string db_file{ "cuvinte.sqlite" };
	private:
		Storage m_db = createStorage(db_file);
	};

}