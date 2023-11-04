module;

export module words;

import <vector>;
import <string>;
import <cstdlib>;
import <ctime>;
import <random>;

namespace skribbl
{
	export class Words
	{
	public:
		Words();
		void addWord(const std::string& word);
		std::string getRandomWord();
		bool wordExists(const std::string& word);
		int getWordCount();
		char SelectRandomLetter(const std::string& word);
	private:
		std::vector<std::string> words;
	};
}
