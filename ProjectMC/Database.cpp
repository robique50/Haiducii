#include "DataBase.h"
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
	void skribbl::DataBase::addUser(const User& user)
	{
		try {
			m_db.insert(user);
			std::cout << "User added succesfully" << std::endl;
		}
		catch (const std::exception& e) {
			std::cerr << "Error at adding user: " << e.what() << std::endl;
		}
	}

	void skribbl::DataBase::populateStorage() {
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

		f.close(); // Close the file when done

		try {
			m_db.insert_range(words.begin(), words.end());
		}
		catch (const std::exception& e) {
			std::cerr << "Error inserting words into database: " << e.what() << std::endl;
		}
	}



	int skribbl::DataBase::getWordsCount()
	{
		int WordsCount = m_db.count<Words>();
		return WordsCount;
	}

	bool skribbl::DataBase::userExists(User user1)
	{
		auto allUsers = m_db.get_all<User>();
		for (auto& user : allUsers)
		{
			if (user1.isEqual(user) == true)
				return true;
		}
		return false;
	}

	void skribbl::DataBase::showUsers()
	{
		auto users = m_db.get_all<User>();

		for (const auto& user : users) {
			std::cout << "ID: " << user.getID() << ", Username: "
				<< user.getUsername() << ", Password: " << user.getPassword() << std::endl;
		}
	}

	void skribbl::DataBase::showWordsFromDatabase()
	{
		auto allWords = m_db.get_all<Words>();

		std::cout << "Words in the database:\n";
		for (auto word : allWords) {
			std::cout << "ID: " << word.getId() << ", Word: " << word.getWord() << "\n";
		}
	}
}