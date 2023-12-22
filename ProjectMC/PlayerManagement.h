#pragma once
#include <vector>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
#include "words.h"
#include <algorithm>
#include <set>
#include <random>
#include <iostream>
#include <cstdlib>
#include <ctime>
namespace sql = sqlite_orm;

import user;
import meetingroom;

namespace skribbl {

    class PlayerManager {

    public:
        PlayerManager() = default;
        int addPlayer(const User& user);
        const std::map<int, User>& getPlayers() const;
        bool doesPlayerExist(const int& playerID) const;
    private:
        std::map<int, User> m_players; 
        
    };
}