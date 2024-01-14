module round;

using namespace skribbl;


Round::Round(int id, const std::string& gameId)
	:
	m_id{ id },
	m_gameId{ gameId },
	m_drawingPlayerName{ "" },
	m_currentWord{ "" },
	m_roundNumber{ 1 },
	m_timeLeft{ 60 }
{
	// Empty
}

Round::Round(int id, const std::string& gameId, const std::string& drawingPlayerName, const std::string& currentWord, const std::set<std::string>& words, uint8_t roundNumber)
	:
	m_id{ id },
	m_gameId{ gameId },
	m_drawingPlayerName{ drawingPlayerName },
	m_currentWord{ currentWord },
	m_words{ words },
	m_roundNumber{ roundNumber },
	m_timeLeft{ 60 }
{
	// Empty
}

void Round::SetId(int id)
{
	m_id = id;
}

void Round::SetGameId(std::string gameId)
{
	m_gameId = gameId;
}

void Round::SetDrawingPlayer(const std::string& drawingPlayerName)
{
	m_drawingPlayerName = drawingPlayerName;
}

void Round::SetCurrentWord(const std::string& currentWord)
{
	m_currentWord = currentWord;
}

void Round::SetWords(const std::set<std::string>& words)
{
	m_words = words;
}

void Round::SetRoundNumber(uint8_t roundNumber)
{
	m_roundNumber = roundNumber;
}

std::string skribbl::Round::SerializeTimes() const noexcept
{
	if (m_time.empty()) {
		return "";
	}

	std::string serializedTimes = std::to_string(m_time.front());
	for (auto it = std::next(m_time.begin()); it != m_time.end(); ++it) {
		serializedTimes += "," + std::to_string(*it);
	}

	return serializedTimes;
}

std::vector<int> skribbl::Round::GetTimes() const noexcept
{
	return m_time;
}

void skribbl::Round::UpdateTimes(int index, int value) noexcept
{
		m_time[index] = value;
}

int Round::GetId() const noexcept
{
	return m_id;
}

std::string Round::GetGameId() const noexcept
{
	return m_gameId;
}

std::string Round::GetDrawingPlayer() const noexcept
{
	return m_drawingPlayerName;
}

std::string Round::GetCurrentWord() const noexcept
{
	return m_currentWord;
}

uint8_t Round::GetRoundNumber() const noexcept
{
	return m_roundNumber;
}

std::string Round::SerializeWords() const noexcept
{
	std::ostringstream oss;
	for (const auto& word : m_words) {
		oss << word << ",";
	}
	std::string result = oss.str();
	if (!result.empty()) {
		result.pop_back();
	}
	return result;
}

void Round::DeserializeWords(const std::string& serializedWords)
{
	std::istringstream ss(serializedWords);
	std::string word;
	while (std::getline(ss, word, ',')) {
		m_words.insert(std::move(word));
	}
}

void skribbl::Round::DeserializeTimes(const std::string& serializedTimes)
{
		std::istringstream ss(serializedTimes);
	std::string point;
	while (std::getline(ss, point, ',')) {
		m_time.push_back(std::stoi(point));
	}
}

void Round::SetTimeLeft(int timeLeft)
{
	m_timeLeft = timeLeft;
}

int Round::GetTimeLeft() const noexcept
{
	return m_timeLeft;
}

void Round::StartTimer()
{
	while (m_timeLeft > 0)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		m_timeLeft--;
	}
}
