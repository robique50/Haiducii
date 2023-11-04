module;

export module game;

import <cstdint>;
import <vector>;
import "User.h";
import "Words.h";

namespace game
{

	export class Game
	{
	public:
		Game(uint16_t numberOfRounds, uint16_t numberOfPlayers, uint16_t currentRound);
		uint16_t getNumberOfPlayers();
		uint16_t getCurrentRound();
		uint16_t getNumberOfRounds();
		void addPlayer(User& player);
		void nextRound();
	private:
		uint16_t m_numberOfRounds;
		uint16_t m_currentRound;
		uint16_t m_numberOfPlayers;
		Words m_currentWord;
		std::vector<User>players;
	};
}