#pragma once
#include <iostream>

class __declspec(dllexport) Score
{
public:
	static void addScore() {
		std::cout<<"Score added\n";
	}
};

