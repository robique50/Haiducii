export module user;
import <string>;

namespace skribbl
{
	export class User
	{
	public:
		User()=default;
		User(const std::string& fullname, const std::string& username, const std::string& password);
		User(int id,const std::string& username, const std::string& password);
		User(int id,const std::string& fullname, const std::string& username, const std::string& password);
		
		void setFullname(const std::string& fullname);
		void setUsername(const std::string& username);
		void setPassword(const std::string& password);
		void setID(int id);
		void SetPoints(int points);
		void AddPoints(int points);
		void SubstractPoints(int points);

		std::string getFullname() const;
		std::string getUsername() const;
		std::string getPassword() const;
		int getID() const;
		int GetPoints() const;
		
		bool isValid() const;
		bool operator<(const User& user);
		bool operator>(const User& user);
		bool operator==(const User& user);
		friend bool operator==(const User& lhs, const User& rhs);

	private:
		int m_id;
		std::string m_fullname;
		std::string m_username;
		std::string m_password;
		int m_points;
		
	};

	export bool operator==(const User& lhs, const User& rhs)
	{
		return lhs.m_id==rhs.m_id;
	}

	

}