#pragma once

class Chat;

class Application
{
public:
    Application(int user_number);
    ~Application();

    void run();

private:
    int _user_number{0};
    Chat** _chat_array{nullptr};
    int _max_chat_number{0};
    int _current_chat_number{0};

    int createAccount();
    int signIn();
};
