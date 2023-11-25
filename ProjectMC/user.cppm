export module user;
import <iostream>;
import <string>;
import <sqlite_orm/sqlite_orm.h>;

namespace skribbl
{
	export class Statistics {
	public:
		Statistics();
		int getTotalScore() const;
		double getAverageScore() const;
		double getAverageTime() const;
		void updateStatistics(int score, double time);
	private:
		int totalScore;
		double averageScore;
		double averageTime;
		int gamesPlayed;
	};

	export class User
	{
	public:
		User(int id,const std::string& username, const std::string& password, const std::string& avatar, bool isDrawing);
		User(std::string username, std::string password);
		User();
		void setUsername(const std::string& username);
		void setPassword(const std::string& password);
		void setID(const int& id);
		std::string getUsername() const;
		std::string getPassword() const;
		std::string getAvatar() const;
		int getID() const;
		int16_t getScore() const;
		void updateStatistics(int score, double time);
		bool isEqual(const User& user);

	private:
		int m_id;
		std::string m_username;
		std::string m_password;
		std::string m_avatar;
		bool m_isDrawing;
		Statistics m_statistics;
	};
}