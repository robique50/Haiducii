import leaderboard;

using skribbl::Leaderboard;

import <iostream>;

void Leaderboard::sortUsersByScore()
{
    
        std::sort(m_users.begin(), m_users.end(), [](const User& user1, const User& user2) {
            return user1.getScore() > user2.getScore();
            });
    }

void Leaderboard::printUsers()
{
    Leaderboard::sortUsersByScore();
    for (auto user : m_users)
        std::cout << user.getFullname << " ";
}
