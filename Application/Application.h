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
 // User* _current_user{nullptr};
    int _max_chat_number{0};
    int _current_chat_number{0}; // Common chat will be created in constructor

    int createAccount();
    int signIn();
    int selectCommonOrPrivate(User* user); 
    int commonChat(User* user) const;
    int privateMenu(User* user);
    int privateChat(User* source_user, User* target_user);
    Chat* getPrivateChat(User* source_user, User* target_user)const;
    int checkingForStringExistence(const std::string& string, const std::string& (User::*get)()const)const;
};
