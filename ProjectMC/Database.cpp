#include "Database.h"

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

	MeetingRoom DataBase::getMeetingRoomByCode(const std::string& code)
	{
		try {
			auto room = m_db.get<MeetingRoom>(sql::where(sql::c(&MeetingRoom::getRoomCode) == code));
			return room;
		}
		catch (const std::exception& e) {
			std::cerr << "Error retrieving meeting room by code: " << e.what() << std::endl;
		}
		return MeetingRoom("");

	}

	bool DataBase::userExists(const User& user)
	{
		auto allUsers = m_db.get_all<User>();
		return std::any_of(allUsers.begin(), allUsers.end(), [&user]
		(const auto& user1) {
				return user.isEqual(user1);
			});
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
		for (const auto& word : allWords) {
			std::cout << "ID: " << word.getId() << ", Word: " << word.getWord() << "\n";
		}
	}

	const std::vector<Words>& DataBase::getRandomWords(const int& numberOfWords)
	{
		auto allWords = m_db.get_all<Words>();

		std::random_device rd;
		std::mt19937 rng(rd());
		std::shuffle(allWords.begin(), allWords.end(), rng);

		std::vector<Words> selectedWords;
		for (const auto& word : allWords) {
			selectedWords.push_back(word);
			if (selectedWords.size() == static_cast<size_t>(numberOfWords)) {
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

	

}