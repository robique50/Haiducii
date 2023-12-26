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
import meetingroom;

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
				"MeetingRoom",
				sql::make_column("roomCode", &MeetingRoom::setRoomCode, &MeetingRoom::getRoomCode, sql::primary_key()),
				sql::make_column("createdByUserId", &MeetingRoom::setCreatedByUserId, &MeetingRoom::getCreatedByUserId),
				sql::make_column("gameState", &MeetingRoom::setGameState, &MeetingRoom::getGameState),
				sql::make_column("playerCount", &MeetingRoom::setPlayerCount, &MeetingRoom::getPlayerCount)
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

		void addMeetingRoom(MeetingRoom& meetingRoom);

		void populateStorage();

		int getWordsCount();

		MeetingRoom getMeetingRoomByCode(const std::string& code);

		bool userExists(const User& user);

		void showUsers();

		void showWordsFromDatabase();

		const std::vector<Words>& getRandomWords(const int& numberOfWords);

		User getUserByUsername(const std::string& username);

		void removeWord(const Words& word);

		void removeUser(const User& user);

		void removeMeetingRoom(const MeetingRoom& meetingRoom);

		void showUsersWithScoreGreaterThan(int score);

		User getUserById(const int& id);

	private:
		const std::string db_file{ "cuvinte.sqlite" };
	private:
		Storage m_db = createStorage(db_file);
	};

}