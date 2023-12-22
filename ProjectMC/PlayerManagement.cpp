#include "PlayerManagement.h"

using skribbl::User;


int skribbl::PlayerManager::addPlayer(const User & user)
{
	m_players[user.getID()] = User(user.getID(),user.getUsername());
	return user.getID();
}

const std::map<int, User>& skribbl::PlayerManager::getPlayers() const
{
	return m_players;
}

bool skribbl::PlayerManager::doesPlayerExist(const int& playerID) const
{
	return m_players.find(playerID) != m_players.end();
}
