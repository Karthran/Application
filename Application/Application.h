#pragma once
#include <string>
#include "Array.h"

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
    Array<Chat> _chat_array;
    Array<User> _user_array;
    // User* _current_user{nullptr};
    int _max_chat_number{0};
    int _current_chat_number{0};  // Common chat will be created in constructor

    int createAccount();
    int signIn();
    int selectCommonOrPrivate(std::shared_ptr<User> user);
    int commonChat(std::shared_ptr<User> user) const;
    int privateMenu(std::shared_ptr<User> user);
    int privateChat(std::shared_ptr<User> source_user, std::shared_ptr<User> target_user);
    int findIndexForChat(std::shared_ptr<Chat> chat) const;
    std::shared_ptr<Chat> getPrivateChat(std::shared_ptr<User> source_user, std::shared_ptr<User> target_user) const;
    int checkingForStringExistence(const std::string& string, const std::string& (User::*get)() const) const;
};
