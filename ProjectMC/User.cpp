module user;

using namespace skribbl;

skribbl::User::User(const std::string& fullname, const std::string& username, const std::string& password)
	: m_fullname{ fullname }, m_username{ username }, m_password{ password }, m_points{ 0 }
{
	//Empty
}


skribbl::User::User(int id, const std::string& username, const std::string& password)
	: m_id{ id }, m_username{ username }, m_password{ password }, m_points{ 0 }
{
	//Empty

}

User::User(int id, const std::string& fullname, const std::string& username, const std::string& password) :
	m_id{ id },
	m_fullname{ fullname },
	m_username{ username },
	m_password{ password },
	m_points{ 0 }
{
	//Empty 
}

void User::setFullname(const std::string& fullname)
{
	m_fullname = fullname;
}

void User::setUsername(const std::string& username)
{
	m_username = username;
}

void User::setPassword(const std::string& password)
{
	m_password = password;
}

void User::setID(int id)
{
	m_id = id;
}

void User::SetPoints(int points)
{
	m_points = points;
}

void User::AddPoints(int points)
{
	m_points += points;
}

void User::SubstractPoints(int points)
{
	m_points -= points;
}

std::string User::getFullname() const
{
	return m_fullname;
}

std::string User::getUsername() const
{
	return m_username;
}

std::string User::getPassword() const
{
	return m_password;
}

int User::getID() const
{
	return m_id;
}

int User::GetPoints() const
{
	return m_points;
}

bool skribbl::User::isValid() const
{
	return !m_username.empty() && !m_password.empty();
}

bool User::operator<(const User& user)
{
	return m_points < user.m_points;
}

bool User::operator>(const User& user)
{
	return m_points > user.m_points;
}

bool User::operator==(const User& user)
{
	return m_id == user.m_id;
}