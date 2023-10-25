#include "Words.h"

Words::Words()
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Words::addWord(const std::string& word)
{
	words.push_back(word);
}
