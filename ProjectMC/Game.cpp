#include "Game.h"
#include <iostream>

Game::Game(uint16_t numberOfRounds, uint16_t numberOfPlayers, uint16_t currentRound) :
	m_numberOfRounds(numberOfPlayers),
	m_numberOfPlayers(numberOfPlayers),
	m_currentRound(currentRound)
{
}

uint16_t Game::getNumberOfPlayers()
{
	return this->m_numberOfPlayers;
}

uint16_t Game::getCurrentRound()
{
	return this->m_currentRound;
}

void Game::nextRound()
{
	if (m_currentRound < m_numberOfRounds)
		m_currentRound++;
	else
		std::cout << "Jocul s-a incheiat." << std::endl;
}

