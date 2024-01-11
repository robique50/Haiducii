#pragma once
#include <string>
#include <vector>
#include <map>
#include <random>
import user;

namespace skribbl {
	class Lobby
	{
		friend class LobbyManager;
	public:
		enum class GameState :uint8_t {
			Waiting,
			Playing,
			Finished
		};
		Lobby(const std::string& code);
		Lobby() = default;
		const std::vector<User>& getPlayers() const;
	protected:
		std::string m_roomCode;
		std::vector<User>m_players;
		GameState m_gameState:2;
	};

	class LobbyManager
	{
	public:
		//LobbyManager();
		bool createLobby(const std::string& code);
		void addPlayerToLobby(const std::string& code, const User& player);
		void removePlayerFromLobby(const std::string& code, const User& player);
		void deleteLobby(const std::string& code);
		bool doesLobbyExist(const std::string& code) const;
		//void startGame(const std::string& code);
		const Lobby& getLobby(const std::string& code) const ;

		std::string generateUniqueCode();
	private:
		std::map<std::string, Lobby>m_lobbies;
	};
}