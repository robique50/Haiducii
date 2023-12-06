export module round;

import <ctime>;
import <time.h>;
import <algorithm>;
import <cctype>;
import <string>;
import <vector>;

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
	private:
		const std::string m_currentWord;
		uint8_t m_time;
		std::vector<std::pair<std::string, uint16_t>>m_guesses;
		//Words m_word;
	};


}