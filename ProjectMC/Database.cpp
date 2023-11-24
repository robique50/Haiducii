#include "DataBase.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
import user;
const std::string db_file = "cuvinte.sqlite";

namespace skribbl
{
	void skribbl::DataBase::addUser(const User& user)
	{
		try {
			db.insert(user);
			std::cout << "User added succesfully" << std::endl;
		}
		catch (const std::exception& e) {
			std::cerr << "Error at adding user: " << e.what() << std::endl;
		}
	}

	void skribbl::DataBase::populateStorage()
	{
		std::vector<Words> words;
		std::string currentWord;
		for (std::ifstream f("listOfWords.txt"); !f.eof();)
		{
			f >> currentWord;
			Words ward{ -1,currentWord };
			words.push_back(ward);
		}
		db.insert_range(words.begin(), words.end());
	}

	void skribbl::DataBase::useDatabase()
	{
		db.sync_schema();
		auto initWordsCount = db.count<Words>();
		if (initWordsCount == 0)
			populateStorage();
	}

	int skribbl::DataBase::getWordsCount()
	{
		int WordsCount = db.count<Words>();
		return WordsCount;
	}

	bool skribbl::DataBase::userExists(User user1)
	{
		auto allUsers = db.get_all<User>();
		for (auto& user : allUsers)
		{
			if (user1.isEqual(user) == true)
				return true;
		}
		return false;
	}

	void skribbl::DataBase::showUsers()
	{
		auto users = db.get_all<User>();

		for (const auto& user : users) {
			std::cout << "ID: " << user.getID() << ", Username: "
				<< user.getUsername() << ", Password: " << user.getPassword() << std::endl;
		}
	}

	void skribbl::DataBase::showWordsFromDatabase()
	{
		auto allWords = db.get_all<Words>();

		std::cout << "Words in the database:\n";
		for (auto word : allWords) {
			std::cout << "ID: " << word.getId() << ", Word: " << word.getWord() << "\n";
		}
	}
}