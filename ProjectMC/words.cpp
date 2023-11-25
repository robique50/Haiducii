#include "words.h"

Words::Words(int id, const std::string& word)
{
    m_id = id;
    m_word = word;
}

int Words::getId()
{
    return m_id;
}

std::string Words::getWord()
{
    return m_word;
}

void Words::setId(int id)
{
    Words::m_id = id;
}

void Words::setWord(std::string word)
{
    Words::m_word = word;
}
