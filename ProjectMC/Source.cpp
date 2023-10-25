#include "User.h"

int main()
{
	User user1("Valy", false);
	User user2("Robert", true);
	User user3("Adrian", false);
	std::cout << user1.getUsername() << " " << user1.getScore() << "\n";
	std::cout << user2.getUsername() << " " << user2.getScore() << "\n";
	std::cout << user3.getUsername() << " " << user3.getScore() << "\n";
}