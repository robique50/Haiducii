#pragma once
#include <iostream>
class User
{
public:
	User(const std::string& username);
private:
	std::string m_username;
	int16_t m_score;
};

