import chatinput;

import <iostream>;
import <string>;

using skribbl::ChatInput;

ChatInput::ChatInput(uint16_t userId, const std::string& input):
    m_userId(userId),
    m_input(input) 
{
}

uint16_t ChatInput::getUserId() const {
        return m_userId;
}

const std::string& ChatInput::getInput() const {
        return m_input;
}

