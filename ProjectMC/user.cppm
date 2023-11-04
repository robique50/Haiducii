export module user;
#include <iostream>;

namespace skribbl
{
	export class User
	{
	public:
		User(const std::string& username, bool isDrawing);
		std::string getUsername();
		int16_t getScore();
	private:
		std::string m_username;
		int16_t m_score;
		bool m_isDrawing;

	};

}