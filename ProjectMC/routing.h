#pragma once
#include <crow.h>
#include <cpr/cpr.h>
#include <iostream>
#include "Database.h"
#include<vector>
#include "openssl/sha.h"

import user;
namespace skribbl
{
	class Routing
	{
	public:
		void Run(skribbl::DataBase& db);
	private:
		
		crow::SimpleApp m_app;
	};
}