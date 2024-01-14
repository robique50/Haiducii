export module round;

import user;

import <vector>;
import <string>;
import <set>;
import <chrono>;
import <thread>;
import <sstream>;

namespace skribbl
{
	export class Round {
	public:

		Round() = default;
		Round(int id, const std::string& gameId);
		Round(int id, const std::string& gameId, const std::string& drawingPlayerName, const std::string& currentWord, const std::set<std::string>& words, uint8_t roundNumber);

		void SetId(int id);
		void SetGameId(std::string gameId);
		void SetDrawingPlayer(const std::string& drawingPlayerName);
		void SetCurrentWord(const std::string& currentWord);
		void SetWords(const std::set<std::string>& words);
		void SetRoundNumber(uint8_t roundNumber);
		std::string SerializeTimes() const noexcept;
		std::vector<int> GetTimes() const noexcept;
		void UpdateTimes(int index, int value) noexcept;

		int GetId() const noexcept;
		std::string GetGameId() const noexcept;
		std::string GetDrawingPlayer() const noexcept;
		std::string GetCurrentWord() const noexcept;
		uint8_t GetRoundNumber() const noexcept;
		std::string SerializeWords() const noexcept;
		void DeserializeWords(const std::string& serializedWords);
		void DeserializeTimes(const std::string& serializedPoints);

		void SetTimeLeft(int timeLeft);
		int GetTimeLeft() const noexcept;

		void StartTimer();

	private:
		int m_id;
		std::string m_gameId;
		std::string m_drawingPlayerName;
		std::string m_currentWord;
		std::set<std::string> m_words;
		uint8_t m_roundNumber;
		int m_timeLeft;
		std::vector<int> m_time;
	};
}