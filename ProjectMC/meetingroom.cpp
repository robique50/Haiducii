import <iostream>;
import meetingroom;

using skribbl::meetingroom;

MeetingRoom::MeetingRoom(const std::string& code) : roomCode(code) {
    std::cout << "The meetingroom was created with code " << roomCode << ".\n";
}

void MeetingRoom::AddPlayer(const User& player) {
    game.AddPlayer(player);
    std::cout << "The player " << player.GetUsername() << " was added to the room " << roomCode << ".\n";
}
