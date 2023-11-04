module;

export module game;

import <cstdint>;
import <vector>;
import "User.h";
import "Words.h";

namespace skribbl
{

	export class Game
	{
	public:
		Game(uint16_t numberOfPlayers, uint16_t currentRound);
		uint16_t getNumberOfPlayers();
		uint16_t getCurrentRound();
		uint16_t getNumberOfRounds();
		void setCurrentRound(const uint16_t& currentRound);
		void setNumberOfPlayers(const uint16_t& numberOfPlayers);
		void addPlayer(User& player);
		bool isGameFinished(const uint16_t& currentRound,
							const uint16_t numberOfRounds);
		bool isFirstRound();
		void nextRound();
	private:
		static const uint16_t m_numberOfRounds=4;
		uint16_t m_currentRound;
		uint16_t m_numberOfPlayers;
		std::vector<User>players;
	};
}