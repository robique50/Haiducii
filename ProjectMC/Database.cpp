import user;
#include "Database.h"
const std::string db_file = "words.sqlite";


Storage db = createStorage(db_file);

void useDatabase()
{
	db.sync_schema();
	auto initWordsCount = db.count<Words>();
	if (initWordsCount == 0)
		populateStorage();
}

void populateStorage()
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

void addUser(const User& user)
{
	try {
		db.insert(user);
		std::cout << "User added succesfully" << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error at adding user: " << e.what() << std::endl;
	}
}


void showWordsCount()
{
	auto WordsCount = db.count<Words>();
	std::cout << "wordsCount = " << WordsCount << '\n';
}
