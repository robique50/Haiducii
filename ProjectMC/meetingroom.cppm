module;

export module meetingroom;

import <vector>;
import <string>;
import <cstdlib>;
import <ctime>;
import <random>;
import game;

namespace skribbl
{
    export class MeetingRoom {
    public:
        Game game;
    private:
        std::string roomCode;
    };
}