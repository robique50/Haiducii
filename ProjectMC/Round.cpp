#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iostream>
import round;

using skribbl::Round;

Round::Round(const std::string& currentWord) 
    : m_currentWord{ currentWord }
{
}

bool Round::CorrectGuess(const std::string& guess)
{
    if (guess.size() != m_currentWord.size())
        return false;

    return std::equal(guess.begin(), guess.end(), m_currentWord.begin(),
        [](char a, char b) {
            return std::tolower(a) == std::tolower(b);
        });
}
std::string Round::getCurrentWord()
{
    return m_currentWord;
}
/*
std::pair<std::string, std::vector<int>> a_doua_jumatate_runda(const std::string& cuvant)
{
    std::vector<int> indici_dezvaluiti;
    for (int i = 0; i < cuvant.size() / 2; ++i) {
        indici_dezvaluiti.push_back(i);
    }
    std::random_shuffle(indici_dezvaluiti.begin(), indici_dezvaluiti.end());
    std::string cuvant_partial = cuvant;
    for (int indice : indici_dezvaluiti) {
        cuvant_partial[indice] = 'a' + rand() % 26;
    }

    return std::make_pair(cuvant_partial, indici_dezvaluiti);
}*/
void Round::ShowLetters()
{
    if (m_time < 30)
    {
        
    }
}
void Round::AddGuess(const std::string& guess, int responseTime)
{
    m_guesses.push_back(std::make_pair(guess, responseTime));
}

int Round::CalculateScore() {
    if (m_guesses.empty()) {
        return -100;
    }
    double totalResponseTime = 0;
    int numCorrectGuesses = 0;
    for (const auto& guess : m_guesses) {
        if (guess.first == m_currentWord) {
            totalResponseTime += guess.second;
            numCorrectGuesses++;
        }
    }

    if (numCorrectGuesses > 0) {
        double averageResponseTime = totalResponseTime / numCorrectGuesses;
        int drawerScore = static_cast<int>((60 - averageResponseTime) / 60.0 * 100);
        return drawerScore;
    }
    else {
        return -100;
    }
}