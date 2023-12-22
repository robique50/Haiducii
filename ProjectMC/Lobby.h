#pragma once
#include <string>
#include <vector>
#include <map>

namespace skribbl {
	class Lobby
	{
		friend class LobbyManager;
	public:
		Lobby(const std::string& code);
		Lobby() = default;
	protected:
		std::string m_roomCode;
		std::vector<int>m_playersID;
		bool m_isGameStarted = false;
	};

	class LobbyManager
	{
	public:
		//LobbyManager();
		bool createLobby(const std::string& code);
		void addPlayerToLobby(const std::string& code, const int& playerID);
		void removePlayerFromLobby(const std::string& code, const int& playerID);
		void deleteLobby(const std::string& code);
		bool doesLobbyExist(const std::string& code) const;
		//void startGame(const std::string& code);

	private:
		std::map<std::string, Lobby>m_lobbies;
	};
}