#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
import round;
import <iostream>;

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
std::pair<std::string, std::vector<int>> ShowLetters(const std::string& cuvant)
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
	int n = m_currentWord.size();
	int numToDisplay = n / 2;
	if (numToDisplay < 1)
    {
		numToDisplay = 1;
	}

	std::string displayedWord = m_currentWord;

		std::random_device rd;
		std::mt19937 gen(rd());
        
	std::vector<int> randomIndices;
	for (int i = 0; i < numToDisplay; ++i)
	{
		int randomIndex;
		do
		{
			randomIndex = std::uniform_int_distribution<int>(0, n - 1)(gen);
		} while (displayedWord[randomIndex] == '_');
		displayedWord[randomIndex] = '_';
    }
		std::cout << "The word is: " << displayedWord << std::endl;
	}
}

void Round::SetState(const RoundState& state)
{
	m_state = state;
}

void skribbl::Round::updateTimer()
{
	while (m_time > 0)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		m_time--;
	}
}

void skribbl::Round::startRound(const int& duration)
{
	int timeToStartDisplay = duration - 30;

	if (timeToStartDisplay <= 0)
	{
		std::cout << "Starting to display letters." << std::endl;
		ShowLetters();
	}
	else
	{
		std::cout << "Round will start in " << timeToStartDisplay << " seconds." << std::endl;

		std::this_thread::sleep_for(std::chrono::seconds(timeToStartDisplay));
		std::cout << "Starting the round now." << std::endl;
		ShowLetters();
	}
}

void Round::AddGuess(const std::string& guess, int responseTime)
{
    m_guesses.insert(std::make_pair(responseTime, guess));
}

int Round::CalculateScore() {
    if (m_guesses.empty()) {
        return -100;
    }
    double totalResponseTime = 0;
    int numCorrectGuesses = 0;
    for (const auto& [responseTime, guess] : m_guesses) {
        if (guess == m_currentWord) {
            totalResponseTime += responseTime;
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