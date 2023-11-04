import user;
import <iostream>;
using skribbl::User;
using skribbl::Statistics;

Statistics::Statistics() : totalScore(0), averageScore(0), averageTime(0), gamesPlayed(0) {}

int Statistics::getTotalScore() const {
    return totalScore;
}

double Statistics::getAverageScore() const {
    return averageScore;
}

double Statistics::getAverageTime() const {
    return averageTime;
}

void Statistics::updateStatistics(int score, double time) {
    totalScore += score;
    averageScore = static_cast<double>(totalScore) / gamesPlayed;
    averageTime = (averageTime * gamesPlayed + time) / (gamesPlayed + 1);
    gamesPlayed++;
}

User::User(const std::string& username, const std::string& password, const std::string& avatar, bool isDrawing)
    : m_username(username), m_password(password), m_avatar(avatar), m_isDrawing(isDrawing) {}

std::string User::getUsername() const {
    return m_username;
}

std::string User::getPassword() const {
    return m_password;
}

std::string User::getAvatar() const {
    return m_avatar;
}

int16_t User::getScore() const {
    return m_statistics.getTotalScore();
}

void User::updateStatistics(int score, double time) {
    m_statistics.updateStatistics(score, time);
}