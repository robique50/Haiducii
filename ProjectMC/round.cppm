export module round;

import <iostream>;
import <ctime>;
import <time.h>;
import <algorithm>;
import <cctype>;
import <string>;
import <vector>;
import <unordered_map>;
import <chrono>;
import <random>;
import <thread>;
import <atomic>;
import <unordered_set>;

export enum class RoundState
{
	Waiting,
	Playing,
	Finished
};

namespace skribbl
{
	export class Round
	{
	public:
		Round(const std::string& currentWord);
		bool CorrectGuess(const std::string& guess);
		std::string getCurrentWord();
		void AddGuess(const std::string& guess, int responseTime);
		int CalculateScore();
		void ShowLetters();
		void SetState(const RoundState& state);
		void startRound(const int& duration);
		void updateTimer();
		bool isTimeUp() const;
		void prepareNextRound();
		std::string getNextWord();
	private:
		const std::string m_currentWord;
		std::atomic<uint16_t>m_time;
		std::unordered_map<uint16_t, std::string>m_guesses;
		RoundState m_state;
		std::unordered_set<std::string> m_wordsList;
		size_t m_nextWordIndex;
		static const uint16_t m_initialDuration{ 60 };
	};


}