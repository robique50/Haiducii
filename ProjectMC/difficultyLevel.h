#pragma once
#include <string>
#include <iostream>
class difficultyLevel
{
    enum Level { Easy, Medium, Hard };

    difficultyLevel(Level initialLevel = Easy) : level(initialLevel) {}

    void setLevel(Level newLevel) {
        level = newLevel;
    }

    Level getLevel() const {
        return level;
    }
   
private:
    Level level;
};

