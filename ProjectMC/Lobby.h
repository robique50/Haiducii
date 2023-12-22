#pragma once
#include <string>
#include <vector>
#include <map>

class Lobby
{
public:
	Lobby(const std::string& code);
private:
	std::string m_roomCode;
	std::vector<int>m_playersID;
	bool m_isGameStarted;
};

class LobbyManager:public Lobby
{
public:
	LobbyManager();
	void createLobby(const std::string& code);
	void addPlayerToLobby(const std::string& code, const int& playerID);
	void removePlayerFromLobby(const std::string& code, const int& playerID);
	void deleteLobby(const std::string& code);
	//void startGame(const std::string& code);

private:
	std::map<std::string,Lobby>m_lobbies;
};
