#include "WordsDatabase.h"

void populateStorage(Storage& storage)
{
	std::vector<Words> words{
		Words{ -1, "Vaca"},
		Words{ -1, "Casa"},
		Words{ -1, "Ocean"},
		Words{ -1, "Dulap"},
		Words{ -1, "Brad"},
	};
	storage.insert_range(words.begin(), words.end());
}