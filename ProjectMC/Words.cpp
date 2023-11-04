#include "Words.h"

Words::Words()
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Words::addWord(const std::string& word)
{
	words.push_back(word);
}

std::string Words::getRandomWord()
{
    if (words.empty()) {
        return "No words available.";
    }

    int randomIndex = std::rand() % words.size();
    return words[randomIndex];
}

bool Words::wordExists(const std::string& word)
{
    for (const std::string& w : words) {
        if (w == word) {
            return true;
        }
    }
    return false;
}

int Words::getWordCount()
{
    return words.size();
}

char Words::SelectRandomLetter(const std::string& word) 
{
    if (word.empty()) {
        throw std::invalid_argument("The word is empty.");
    }

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<size_t> distribution(0, word.size() - 1);
    size_t randomIndex = distribution(generator);
    return word[randomIndex];
}

