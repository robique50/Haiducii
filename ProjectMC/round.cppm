export module round;
import "Words.h";
import <algorithm> ;
import <cctype>;

namespace skribbl
{
	export class Round
	{
	public:
		const std::string m_currentWord;
		uint8_t m_time;
		std::vector<std::pair<std::string, uint16_t>>m_guesses;
		Words m_word;
	private:
		Round(const std::string& currentWord);
		bool CorrectGuess(const std::string& guess);
		void AddGuess(const std::string& guess, int responseTime);
		int CalculateScore();
		void ShowLetters();
	};


}