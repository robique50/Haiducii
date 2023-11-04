module;

import <string>;
//impport server;
export module client;

namespace skribbl
{
    class Client {
    public:
        Client();
        //Server& server;

        void SetUsername(std::string username);

        std::string GetUsername();

    private:
        std::string username;
    };
}