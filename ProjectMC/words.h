#include<iostream>
#include<string>

class Words {
public:
	int getId();
	std::string getWord();
private:
	int m_id;
	std::string m_word;
};