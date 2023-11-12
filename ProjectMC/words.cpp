#include "words.h"

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
