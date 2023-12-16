import game;

using skribbl::Game;

import <iostream>;

uint16_t Game::m_numberOfRounds = 4;

Game::Game(uint16_t numberOfPlayers, uint16_t currentRound) :
	m_numberOfPlayers{ numberOfPlayers },
	m_currentRound{ currentRound }
{}

uint16_t Game::getNumberOfPlayers()
{
	return this->m_numberOfPlayers;
}

uint16_t Game::getCurrentRound()
{
	return this->m_currentRound;
}

uint16_t Game::getNumberOfRounds()
{
	return this->m_numberOfRounds;
}

void skribbl::Game::setNumberOfRounds(const uint16_t& numberOfRounds)
{
	m_numberOfRounds = numberOfRounds;
}

void skribbl::Game::StartGame()
{

}

void skribbl::Game::setCurrentRound(const uint16_t& currentRound)
{
	this->m_currentRound = currentRound;
}

void skribbl::Game::setNumberOfPlayers(const uint16_t& numberOfPlayers)
{
	this->m_numberOfPlayers = numberOfPlayers;
}

void skribbl::Game::addPlayer(const User& player)
{
	this->players.push_back(player);
}

bool skribbl::Game::isGameFinished(const uint16_t& currentRound, const uint16_t& numberOfRounds)
{
	return currentRound == numberOfRounds;
}

bool skribbl::Game::isFirstRound()
{
	return this->m_currentRound == 1;
}

void Game::nextRound()
{
	if (m_currentRound < m_numberOfRounds)
		m_currentRound++;
	else
		std::cout << "Jocul s-a incheiat." << std::endl;
}
