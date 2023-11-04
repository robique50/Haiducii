export module chatinput;

import <iostream>;
import <string>;

namespace skribbl 
{
    export class ChatInput {
    public:
        ChatInput(uint16_t userId, const std::string& input);
        uint16_t getUserId() const;
        const std::string& getInput() const;

    private:
        uint16_t m_userId;
        std::string m_input;
    };
}

