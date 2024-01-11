#include "Lobby.h"

skribbl::Lobby::Lobby(const std::string& code) :m_roomCode{ code }
{}

const std::vector < skribbl::User > & skribbl::Lobby::getPlayers() const
{
	return m_players;
}



bool skribbl::LobbyManager::createLobby(const std::string& code)
{
	if (m_lobbies.find(code) != m_lobbies.end()) {
		return false;
	}
	m_lobbies[code] = Lobby(code);
	return true;
}

void skribbl::LobbyManager::addPlayerToLobby(const std::string& code, const User& player)
{
	auto it = m_lobbies.find(code);
	if (it != m_lobbies.end()) {
		it->second.m_players.push_back(player);
	}
}

void skribbl::LobbyManager::removePlayerFromLobby(const std::string& code, const User& player)
{
	auto lobbyIt = m_lobbies.find(code);
	if (lobbyIt != m_lobbies.end()) {
		auto& players = lobbyIt->second.m_players;
		auto playerIt = std::find(players.begin(), players.end(), player);

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

const  skribbl::Lobby& skribbl::LobbyManager::getLobby(const std::string& code) const
{
	return m_lobbies.at(code);
}

std::string skribbl::LobbyManager::generateUniqueCode()
{
		std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		std::random_device rd;
		std::mt19937 generator(rd());
		std::uniform_int_distribution<> distribution(0, chars.size() - 1);

		std::string code;
		int codeLength = 8;

		for (int i = 0; i < codeLength; ++i) {
			code += chars[distribution(generator)];
		}

		return code;
}
