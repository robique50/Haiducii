import user;
using skribbl::User;
User::User(const std::string& username, bool isDrawing) :m_username(username), m_score(0), m_isDrawing(isDrawing)
{
}

std::string User::getUsername()
{
	return m_username;
}

int16_t User::getScore()
{
	return m_score;