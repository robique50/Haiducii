#pragma once
#include <cpr/cpr.h>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

namespace skribbl {

	class Client
	{
	public:
		Client(const std::string& serverUrl);
		std::unordered_set<std::string> loadWordsFromServer();
	private:
		std::string m_serverUrl;

		std::string makeHTTPRequest(const std::string& url);
		std::unordered_set<std::string> parseWordsResponse(const std::string& jsonResponse);
	};
}


