#include "words.h"
#include <random>

skribbl::Words::Words(int id, const std::string& word) :m_id(id), m_word(word)
{
}

int skribbl::Words::getId() const
{
	return m_id;
}

std::string skribbl::Words::getWord() const
{
	return m_word;
}

void skribbl::Words::setId(int m_id)
{
		this->m_id = m_id;
}

void skribbl::Words::setWord(std::string word)
{
		this->m_word = word;
}

std::string skribbl::Words::toString() const
{
	return m_word;
}

std::string skribbl::Words::getRandomHalfLetters() const
{
    std::string shuffled = m_word;
        std::random_device rd;
        std::mt19937 gen(rd());
    std::shuffle(shuffled.begin(), shuffled.end(), gen);

    return shuffled.substr(0, shuffled.size() / 2);
    }

