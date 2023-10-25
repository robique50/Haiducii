#include "Round.h"
Round::Round(const std::string &currentWord): m_currentWord(currentWord)
{
}

bool Round::CorrectGuess(const std::string & guess)
{
    if (guess.size() != m_currentWord.size()) 
        return false;

    return std::equal(guess.begin(), guess.end(), m_currentWord.begin(),
        [](char a, char b) {
            return std::tolower(a) == std::tolower(b);
        });
}

