module;

export module game;
import <iostream>;
import <cstdint>;
import <vector>;
import user;

namespace skribbl
{
	export class Game
	{
	public:
		//Game() {}
		Game(uint16_t numberOfPlayers, uint16_t currentRound);//TODO :Vectorul de playeri 
		uint16_t getNumberOfPlayers();
		uint16_t getCurrentRound();
		uint16_t getNumberOfRounds();
		void StartGame();
		void setCurrentRound(const uint16_t& currentRound);//nu trebuie
		void setNumberOfPlayers(const uint16_t& numberOfPlayers);//nu trebuie
		void addPlayer(const User& player);
		bool isGameFinished(const uint16_t& currentRound,
							const uint16_t& numberOfRounds);
		bool isFirstRound();
		void nextRound();
	private:
		static const uint16_t m_numberOfRounds=4;
		uint16_t m_currentRound;
		uint16_t m_numberOfPlayers;
		std::vector<User>players;
	};
}