export module game;

import <vector>;
import <string>;
import <array>;
import <sstream>;
import <algorithm>;
import <set>;

import user;  
import round;

namespace skribbl
{
	export class Game
	{
	private:
		enum class GameStatus : uint8_t
		{
			UNKNOWN,
			WAITING,
			INPROGRESS,
			FINISHED
		};

	public:
		Game() = default;
		Game(int id, const User& player, const std::string& gameCode, size_t currentPlayers);

		void StartGame(std::set<std::string> words);
		void EndGame();

		void AddPlayer(const User& player);
		void RemovePlayer(const User& player);

		void DeserializePlayers(const std::string& serializedPlayers);
		int GetCurrentPlayers() const;
		int GetGameStatusAsInt() const;
		std::string SerializePlayers() const;
		std::string GetGameCode() const noexcept;
		const GameStatus GetGameStatus() const noexcept;
		const std::vector<User>& GetPlayers() const noexcept;
		int GetId() const noexcept;
		int GetPlayerScore(const std::string& username) const noexcept;
		int GetNoOfRounds() const noexcept;
		std::string GetChat() const noexcept;
		std::string GetDrawingPlayer() const noexcept;
		uint8_t GetRoundNumber() const noexcept;

		void SetGameCode(const std::string& gameCode);
		void SetGameStatus(GameStatus status);
		void SetCurrentPlayers(int currentPlayers);
		void SetId(int id);
		void SetPlayers(const std::vector<User>& players);
		void SetGameStatusInt(int status);
		void SetChat(const std::string& chat);

		void AddPoints(User& player, const int& timeLeft);
		void SubstractPoints(User& player);
		void AddPointsForTheDrawer(User& player);
		void SubstractPointsForTheDrawer(User& player);
		void AverageTime(const int& timeLeft);
		void SetPlayerScore(const std::string& username, int score);

	private:
		int m_id;
		static const size_t kNoOfRounds{ 4 };
		Round m_round;
		size_t m_currentPlayers;
		std::string m_gameCode;
		std::vector<User>m_players;
		GameStatus m_gameStatus{ GameStatus::UNKNOWN };

		float m_averageTime = 0;

		std::string m_chat;
	};
}
