#include<iostream>
#include<string>

class Words {
public:
	Words(int id,const std::string& word);
	Words() = default;
	int getId();
	std::string getWord();
	void setId(int m_id);
	void setWord(std::string word);
private:
	int m_id;
	std::string m_word;
};