#include "WordsDatabase.h"

void populateStorage(Storage& storage)
{
	std::vector<Word> words;
	std::string currentWord;
	for (std::ifstream f("listOfWords.txt"); !f.eof();)
	{
		f >> currentWord;
		Word ward{ -1,currentWord };
		words.push_back(ward);
		
	}
	storage.insert_range(words.begin(), words.end());
}