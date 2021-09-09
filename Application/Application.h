#pragma once
#include <string>
class Chat;
class User;

class Application
{
public:
    Application(int user_number);
    ~Application();

    void run();

private:
    int _max_user_number{0};
    int _current_user_number{0};
    Chat** _chat_array{nullptr};
    User** _user_array{nullptr};
    int _max_chat_number{0};
    int _current_chat_number{0};

    int createAccount();
    int signIn();
    bool checkingForStringExistence(const std::string& string, const std::string& (User::*get)()const);
};
