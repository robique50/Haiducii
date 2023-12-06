import meetingroom;

namespace skribbl
{
    MeetingRoom::MeetingRoom(const std::string& code) : roomCode(code), createdByUserId(0), gameState("waiting"), playerCount(0) {
        std::cout << "The meeting room was created with code " << roomCode << ".\n";
    }

    void MeetingRoom::addPlayer(const User& player)
    {
        playerCount++;
        std::cout << "Player " << player.getUsername() << " was added to the meeting room.\n";
    }

    void MeetingRoom::removePlayer(const User& player)
    {
		playerCount--;
		std::cout << "Player " << player.getUsername() << " was removed from the meeting room.\n";
    }

    void MeetingRoom::startGame()
    {
        if (playerCount < 2) {
            std::cout << "Not enough players in the room " << roomCode << ".\n";
            return;
        }
        gameState = "in progress";
        std::cout << "The game started in the room " << roomCode << "!\n";
    }
    }

    void MeetingRoom::endGame()
    {
        gameState = "finished";
		std::cout << "The game ended in the room " << roomCode << ".\n";
    }

    void MeetingRoom::setRoomCode(const std::string& code)
    {

    }

    std::string MeetingRoom::getRoomCode() const
    {
        return roomCode;
    }

    void MeetingRoom::setCreatedByUserId(int userId)
    {
    }

    int MeetingRoom::getCreatedByUserId() const
    {
        return 0;
    }

    void MeetingRoom::setGameState(const std::string& state)
    {
    }

    std::string MeetingRoom::getGameState() const
    {
        return std::string();
    }

    void MeetingRoom::setPlayerCount(int count)
    {
    }

    int MeetingRoom::getPlayerCount() const
    {
        return 0;
    }




   
}