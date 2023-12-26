	export module meetingroom;

	import <string>;
	import <iostream>;
	import <vector>;
	import <random>;
	import user;

	namespace skribbl
	{
		export class MeetingRoom {
		public:
			MeetingRoom();
			MeetingRoom(const std::string& code);
			void addPlayer(const User& player);
			void removePlayer(const User& player);
			void startGame();
			void endGame();
			void setRoomCode(const std::string& code);
			std::string getRoomCode() const;
			void setCreatedByUserId(int userId);
			int getCreatedByUserId() const;
			void setGameState(const std::string& state);
			std::string getGameState() const;
			void setPlayerCount(int count);
			int getPlayerCount() const;
			static std::string generateUniqueCode();

		private:
			std::string roomCode;
			std::vector<User> players;
			int createdByUserId;
			std::string gameState;//enum class
			int playerCount;
			// Other necessary attributes as needed
		};
	}
