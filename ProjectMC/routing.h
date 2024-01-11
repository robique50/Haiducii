#pragma once
#include <crow.h>
#include <cpr/cpr.h>
#include <iostream>
#include "Database.h"
#include <vector>
#include "words.h"
#include "PlayerManagement.h"
#include "Lobby.h"
#include <random>

import user;
using skribbl::PlayerManager;
using skribbl::LobbyManager;

namespace skribbl
{
	class Routing
	{
	public:
		void Run(skribbl::DataBase& db);
	private:
		LobbyManager lobbyManager;
		crow::SimpleApp m_app;
	};
}
