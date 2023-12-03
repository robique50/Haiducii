#include "words.h"

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

