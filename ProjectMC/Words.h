#pragma once

#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>

class Words
{
public:
	Words();
	void addWord(const std::string& word);
	std::string getRandomWord();
	bool wordExists(const std::string& word);
	int getWordCount();
	char SelectRandomLetter(const std::string& word);
private:
	std::vector<std::string> words;
};

