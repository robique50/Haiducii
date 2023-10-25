#pragma once
#include <cstdint>
#include "Words.h"

class Game
{
public:
	Game(uint16_t numberOfRounds, uint16_t numberOfPlayers,uint16_t currentRound);
	uint16_t getNumberOfPlayers();
	uint16_t getCurrentRound();
	void nextRound();
private:
	uint16_t m_numberOfRounds;
	uint16_t m_currentRound;
	uint16_t m_numberOfPlayers;
	Words m_currentWord;
};

