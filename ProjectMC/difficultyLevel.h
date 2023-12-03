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

    bool isDifficult() const {
        return level == Hard;
    }

    void increaseDifficulty() {
        if (level != Hard) {
            level = static_cast<Level>(level + 1);
        }
    }

    bool isMaxDifficulty() const {
        return level == Hard;
    }
   
private:
    Level level;
};

