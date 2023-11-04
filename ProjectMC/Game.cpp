import game;

using game::Game;


Game::Game(uint16_t numberOfPlayers, uint16_t currentRound):
	m_numberOfPlayers{numberOfPlayers},
	m_currentRound{currentRound}
{}

uint16_t Game::getNumberOfPlayers()
{
	return this->m_numberOfPlayers;
}

uint16_t Game::getCurrentRound()
{
	return this->m_currentRound;
}

uint16_t Game::getNumberOfRounds()
{
	return this->m_numberOfRounds;
}

void game::Game::setCurrentRound(const uint16_t& currentRound)
{
	this->m_currentRound = currentRound;
}

void game::Game::setNumberOfPlayers(const uint16_t& numberOfPlayers)
{
	this->m_numberOfPlayers = numberOfPlayers;
}

void Game::addPlayer(User& player)
{
	players.push_back(player);
}

void Game::nextRound()
{
	if (m_currentRound < m_numberOfRounds)
		m_currentRound++;
	else
		std::cout << "Jocul s-a incheiat." << std::endl;
}