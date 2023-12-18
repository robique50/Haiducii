#include "client.h"

skribbl::Client::Client(const std::string& serverUrl) : m_serverUrl{ serverUrl }
{}

std::unordered_set<std::string> skribbl::Client::loadWordsFromServer()
{
	std::string response{ makeHTTPRequest(m_serverUrl + "/getwords") };
	return parseWordsResponse(response);

}

std::string skribbl::Client::makeHTTPRequest(const std::string& url)
{
	cpr::Response r = cpr::Get(cpr::Url{ url });
	return r.text;
}

std::unordered_set<std::string> skribbl::Client::parseWordsResponse(const std::string& jsonResponse)
{
	std::unordered_set<std::string> words;
	auto json = nlohmann::json::parse(jsonResponse);

	for (const auto& item : json) {
		words.insert(item["word"].get<std::string>());
	}
	return words;
}