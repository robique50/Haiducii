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
		int getGamesPlayed() const;
		void updateStatistics(int score, double time);
	private:
		int m_totalScore;
		double m_averageScore;
		double m_averageTime;
		int m_gamesPlayed;
	};

	export class User
	{
	public:
		User(int id, const std::string& fullname, const std::string& username, const std::string& password, bool isDrawing);
		User(int id, const std::string& username, const std::string& password);
		User(std::string& fullname, std::string& username, std::string& password);
		User();
		User(int id, std::string username);
		void setFullname(const std::string& fullname);
		void setUsername(const std::string& username);
		void setPassword(const std::string& password);
		void setID(const int& id);
		std::string getFullname() const;
		std::string getUsername() const;
		std::string getPassword() const;
		int getID() const;
		int16_t getScore() const;
		void updateStatistics(int score, double time);
		bool isEqual(const User& user) const;
		bool isValid() const;
		const Statistics& getStatistics() const;

	private:
		int m_id;
		std::string m_fullname;
		std::string m_username;
		std::string m_password;
		bool m_isDrawing;
		Statistics m_statistics;
	};
}