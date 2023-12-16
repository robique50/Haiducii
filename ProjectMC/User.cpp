import user;
import <iostream>;
using skribbl::User;
using skribbl::Statistics;

Statistics::Statistics() :
	m_totalScore{ 0 },
	m_averageScore{ 0 },
	m_averageTime{ 0 },
	m_gamesPlayed{ 0 }
{}

int Statistics::getTotalScore() const {
    return m_totalScore;
}

double Statistics::getAverageScore() const {
    return m_averageScore;
}

double Statistics::getAverageTime() const {
    return m_averageTime;
}

void Statistics::updateStatistics(int score, double time) {
    m_totalScore += score;
    m_averageScore = static_cast<double>(m_totalScore) / m_gamesPlayed;
    m_averageTime = (m_averageTime * m_gamesPlayed + time) / (m_gamesPlayed + 1);
    m_gamesPlayed++;
}

User::User(int id, const std::string& fullname, const std::string& username, const std::string& password, bool isDrawing)
    : m_id(id),m_fullname(fullname), m_username(username), m_password(password), m_isDrawing(isDrawing) {}

skribbl::User::User(int id, const std::string& username, const std::string& password):
    m_id(id),m_username(username),m_password(password)
{}

User::User(std::string& fullname,std::string& username, std::string& password) 
    : m_fullname(fullname), m_username(std::move(username)), m_password(std::move(password))
{}

User::User() = default;

void skribbl::User::setFullname(const std::string& fullname)
{
	User::m_fullname = fullname;
}

void skribbl::User::setUsername(const std::string& username)
{
    User::m_username = username;
}

void skribbl::User::setPassword(const std::string& password)
{
    User::m_password = password;
}

void skribbl::User::setID(const int& id)
{
    User::m_id = id;
}

std::string skribbl::User::getFullname() const
{
    return m_fullname;
}

std::string User::getUsername() const {
    return m_username;
}

std::string User::getPassword() const {
    return m_password;
}

int skribbl::User::getID() const
{
    return m_id;
}

int16_t User::getScore() const {
    return m_statistics.getTotalScore();
}

void User::updateStatistics(int score, double time) {
    m_statistics.updateStatistics(score, time);
}

bool skribbl::User::isEqual(const User& user) const
{
     if (m_username == user.getUsername() && m_password == user.getPassword())
            return true;
     return false;
}

bool skribbl::User::isValid() const
{
    return !m_username.empty();
}