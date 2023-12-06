export module meetingroom;

import <string>;
import <iostream>;
import user;

export namespace skribbl
{
    class MeetingRoom {
    public:
        MeetingRoom(const std::string& code);
        void AddPlayer(const User& player);
        void RemovePlayer(const User& player);
        void StartGame();
        void EndGame();
        void SetRoomCode(const std::string& code);
        std::string GetRoomCode() const;
        void SetCreatedByUserId(int userId);
        int GetCreatedByUserId() const;
        void SetGameState(const std::string& state);
        std::string GetGameState() const;
        void SetPlayerCount(int count);
        int GetPlayerCount() const;

    private:
        std::string roomCode;
        int createdByUserId;
        std::string gameState;
        int playerCount;
        // Other necessary attributes as needed
    };
}
