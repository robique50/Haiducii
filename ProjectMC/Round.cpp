import round;
import <iostream>;
import <random>;

using skribbl::Round;

Round::Round(const std::string& currentWord)
	: m_currentWord{ currentWord }
{
}

bool Round::CorrectGuess(const std::string& guess)
{
	if (guess.size() != m_currentWord.size())
		return false;

	return std::equal(guess.begin(), guess.end(), m_currentWord.begin(),
		[](char a, char b) {
			return std::tolower(a) == std::tolower(b);
		});
}
std::string Round::getCurrentWord()
{
	return m_currentWord;
}

void Round::ShowLetters()
{
	int interval = 2;
	size_t n = m_currentWord.size();
	int numToDisplay = n / 2;
	if (numToDisplay < 1)
	{
		numToDisplay = 1;
	}
	std::string displayedWord(n, '_');
	std::random_device rd;
	std::mt19937 gen(rd());
	int displayedIndex = 0;
	while (numToDisplay > 0)
	{
		int randomIndex;
		do
		{
			randomIndex = std::uniform_int_distribution<int>(0, n - 1)(gen);
		} while (displayedWord[randomIndex] != '_');
		displayedWord[randomIndex] = m_currentWord[randomIndex];
		std::cout << displayedWord << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(interval));
		displayedIndex = randomIndex;
		numToDisplay--;
	}
}

void Round::SetState(const RoundState& state)
{
	m_state = state;
}

void Round::updateTimer()
{
	while (m_time > 0)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		m_time--;
	}
}

bool Round::isTimeUp() const
{
	return m_time <= 0;
}

void Round::prepareNextRound()
{
	SetState(RoundState::Waiting);
	m_guesses.clear();
	//m_currentWord = getNextWord();
	m_time = m_initialDuration;
}

std::string Round::getNextWord()
{
	static std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<> dist(0, m_wordsList.size() - 1);

	auto it = m_wordsList.begin();
	std::advance(it, dist(gen));

	std::string word = *it;
	m_wordsList.erase(it);

	return word;
}

void Round::startRound(const int& duration)
{
	SetState(RoundState::Playing);
	m_time = duration;

	std::thread timerThread(&Round::updateTimer, this);
	timerThread.detach();

	while (!isTimeUp()) {
		//checkAndProcessGuesses(); //TO DO
		if (m_time == duration / 2) {
			ShowLetters();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	//TO DO : calculate score for all players
	SetState(RoundState::Finished);
	prepareNextRound();
}

void Round::AddGuess(const std::string& guess, int responseTime)
{
	m_guesses.insert(std::make_pair(responseTime, guess));
}

int Round::CalculateScore() {
	if (m_guesses.empty()) {
		return -100;
	}
	double totalResponseTime = 0;
	int numCorrectGuesses = 0;
	for (const auto& [responseTime, guess] : m_guesses) {
		if (guess == m_currentWord) {
			totalResponseTime += responseTime;
			numCorrectGuesses++;
		}
	}

	if (numCorrectGuesses > 0) {
		double averageResponseTime = totalResponseTime / numCorrectGuesses;
		int drawerScore = static_cast<int>((60 - averageResponseTime) / 60.0 * 100);
		return drawerScore;
	}
	else {
		return -100;
	}
}