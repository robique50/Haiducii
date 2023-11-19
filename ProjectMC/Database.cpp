import user;
#include "Database.h"

void populateStorage(Storage& storage)
{
	std::vector<Words> words;
	std::string currentWord;
	for (std::ifstream f("listOfWords.txt"); !f.eof();)
	{
		f >> currentWord;
		Words ward{ -1,currentWord };
		words.push_back(ward);
	}
	storage.insert_range(words.begin(), words.end());
}

void addUser(Storage& storage, const User& user)
{
	try {
		storage.insert(user);
		std::cout << "User added succesfully" << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error at adding user: " << e.what() << std::endl;
	}
}