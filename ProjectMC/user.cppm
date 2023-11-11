export module user;
import <iostream>;
import <string>;
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
		User(const std::string& username, const std::string& password, const std::string& avatar, bool isDrawing);
		std::string getUsername() const;
		std::string getPassword() const;
		std::string getAvatar() const;
		int16_t getScore() const;
		void updateStatistics(int score, double time);
		//int getId();
	private:
		std::string m_username;
		std::string m_password;
		std::string m_avatar;
		bool m_isDrawing;
		Statistics m_statistics;
		//int id;
	};

	
}