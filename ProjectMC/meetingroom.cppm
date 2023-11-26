module; 

export module meetingroom;

import <vector>;
import <string>;
import <cstdlib>;
import <ctime>;
import <random>;
import user;
import game;

namespace skribbl
{
    export class MeetingRoom {
    public:
        Game game;
        MeetingRoom(const std::string& code);
        void AddPlayer(const User& jucator);
        void StartGame();
    private:
        std::string roomCode;
    };
}