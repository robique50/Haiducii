module;

export module leaderboard;
import <iostream>;
import <cstdint>;
import <vector>;
import <algorithm>;
import user;

namespace skribbl
{
	export class Leaderboard
	{
	public:
        void sortUsersByScore();
         
	private:
		std::vector <User> m_users;
	};
}