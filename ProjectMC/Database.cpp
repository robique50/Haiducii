#include "Database.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

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

	void DataBase::addMeetingRoom(const MeetingRoom& meetingRoom)
	{
		try {
			m_db.replace(meetingRoom);
			std::cout << "Meeting room added succesfully" << std::endl;
		}
		catch (const std::exception& e) {
			std::cerr << "Error at adding meeting room: " << e.what() << std::endl;
		}
	}

	void DataBase::populateStorage() {
		std::vector<Words> words;
		std::string currentWord;
		std::ifstream f("listOfWords.txt");

		// Check if the file is successfully opened
		if (!f.is_open()) {
			std::cerr << "Unable to open listOfWords.txt" << std::endl;
			return;
		}

		while (f >> currentWord) {
			std::cout << currentWord << std::endl; // Optional: for debugging
			Words word{ -1, currentWord }; // Assuming Words constructor takes id and word
			words.push_back(word);
		}
		m_db.insert_range(words.begin(), words.end());
	}

	int DataBase::getWordsCount()
	{
		int WordsCount = m_db.count<Words>();
		return WordsCount;
	}

	MeetingRoom DataBase::getMeetingRoomByCode(const std::string& code)
	{
		try{
		auto room = m_db.get<MeetingRoom>(sql::where(sql::c(&MeetingRoom::getRoomCode) == code));
		return room;
		}
			catch (const std::exception& e) {
			std::cerr << "Error retrieving meeting room by code: " << e.what() << std::endl;
		}
		return MeetingRoom(""); // Return an empty or default MeetingRoom object in case of error

	}

	bool DataBase::userExists(User user1)
	{
		auto allUsers = m_db.get_all<User>();
		for (auto& user : allUsers)
		{
			if (user1.isEqual(user) == true)
				return true;
		}
		return false;
	}

	void DataBase::showUsers()
	{
		auto users = m_db.get_all<User>();

		for (const auto& user : users) {
			std::cout << "ID: " << user.getID() << ", Username: "
				<< user.getUsername() << ", Password: " << user.getPassword() << std::endl;
		}
	}


	void DataBase::showWordsFromDatabase()
	{
		auto allWords = m_db.get_all<Words>();

		std::cout << "Words in the database:\n";
		for (auto word : allWords) {
			std::cout << "ID: " << word.getId() << ", Word: " << word.getWord() << "\n";
		}
	}

	std::vector<Words> DataBase::getRandomWords(const int& numberOfWords)
	{
		auto allWords = m_db.get_all<Words>();

		std::random_device rd;
		std::default_random_engine rng(rd());
		std::shuffle(allWords.begin(), allWords.end(), rng);
		int wordsToRetrieve = std::min(numberOfWords, static_cast<int>(allWords.size()));
		std::set<std::string> uniqueWords;
		std::vector<Words> selectedWords;
		for (auto word : allWords)
		{
			if (uniqueWords.insert(word.getWord()).second)
			{
				selectedWords.push_back(word);

				if (selectedWords.size() == wordsToRetrieve)
					break;
			}
		}

		return selectedWords;

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
		try {
			m_db.remove<Words>(word.getId());
			std::cout << "Word removed successfully" << std::endl;
		}
		catch (const std::exception& e) {
			std::cerr << "Error at removing word: " << e.what() << std::endl;
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

	void DataBase::removeMeetingRoom(const MeetingRoom& meetingRoom)
	{
		try {
			m_db.remove<MeetingRoom>(meetingRoom.getRoomCode());
			std::cout << "Meeting room removed successfully" << std::endl;
		}
		catch (const std::exception& e) {
			std::cerr << "Error at removing meeting room: " << e.what() << std::endl;
		}
	}

	void DataBase::showUsersWithScoreGreaterThan(int score)
	{
		
		auto users = m_db.get_all<User>(sql::where(sql::c(&User::getScore) > score));

		for (const auto& user : users)
		{
			std::cout << "ID: " << user.getID() << ", Username: " << user.getUsername() << ", Score: " << user.getScore() << std::endl;
		}
	}
}

