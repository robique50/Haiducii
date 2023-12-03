#pragma once
#include<iostream>
#include<string>

namespace skribbl {

	class Words {
	public:
		Words(int id, const std::string& word);
		int getId() const;
		std::string getWord() const;
		void setId(int m_id);
		void setWord(std::string word);
	private:
		int m_id;
		std::string m_word;
	public:

		Words() = default;
	};

}