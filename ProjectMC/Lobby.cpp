#include "Lobby.h"

skribbl::Lobby::Lobby(const std::string& code) :m_roomCode{ code }
{}

bool skribbl::LobbyManager::createLobby(const std::string& code)
{
	if (m_lobbies.find(code) != m_lobbies.end()) {
		return false;
	}
	m_lobbies[code] = Lobby(code);
	return true;
}

void skribbl::LobbyManager::addPlayerToLobby(const std::string& code, const int& playerID)
{
	auto it = m_lobbies.find(code);
	if (it != m_lobbies.end()) {
		it->second.m_playersID.push_back(playerID);
	}
}

void skribbl::LobbyManager::removePlayerFromLobby(const std::string& code, const int& playerID)
{
	auto lobbyIt = m_lobbies.find(code);
	if (lobbyIt != m_lobbies.end()) {
		auto& players = lobbyIt->second.m_playersID;
		auto playerIt = std::find(players.begin(), players.end(), playerID);

		if (playerIt != players.end()) {
			players.erase(playerIt);
		}
	}
}

void skribbl::LobbyManager::deleteLobby(const std::string& code)
{
	auto it = m_lobbies.find(code);
	if (it != m_lobbies.end()) {
		m_lobbies.erase(it);
	}
}

bool skribbl::LobbyManager::doesLobbyExist(const std::string& code) const
{
	return m_lobbies.find(code) != m_lobbies.end();
}
