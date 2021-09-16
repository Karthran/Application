#pragma once
#include <string>
#include "Array.h"

class Chat;
class User;

class Application
{
public:
    Application();

    void run();

private:
    int _current_user_number{0};
    Array<Chat> _chat_array;
    Array<User> _user_array;
    int _current_chat_number{1};  // Common chat will be created in constructor

    int createAccount();
    void createAccount_inputName(std::string& name) const;
    void createAccount_inputLogin(std::string& login) const;
    void createAccount_inputPassword(std::string& password) const;

    int signIn();
    int signIn_inputLogin(std::string& user_login) const;
    int signIn_inputPassword(std::string& user_password, int index) const;

    int selectCommonOrPrivate(const std::shared_ptr<User>& user);

    int commonChat(const std::shared_ptr<User>& user) const;
    void commonChat_addMessage(const std::shared_ptr<User>& user) const;
    void commonChat_editMessage(const std::shared_ptr<User>& user) const;
    void commonChat_deleteMessage(const std::shared_ptr<User>& user) const;

    int privateMenu(const std::shared_ptr<User>& user);
    void privateMenu_viewUsersNames() const;
    int privateMenu_selectByName(const std::shared_ptr<User>& user) const;
    void privateMenu_selectByID(const std::shared_ptr<User>& user);

    int privateChat(const std::shared_ptr<User>& source_user, const std::shared_ptr<User>& target_user);
    void privateChat_addMessage(const std::shared_ptr<User>& source_user, const std::shared_ptr<User>& target_user, std::shared_ptr<Chat>& chat);
    void privateChat_editMessage(const std::shared_ptr<User>& source_user, const std::shared_ptr<User>& target_user, const std::shared_ptr<Chat>& chat) const;
    void privateChat_deleteMessage(const std::shared_ptr<User>& source_user, const std::shared_ptr<User>& target_user, const std::shared_ptr<Chat>& chat) const;

    int findIndexForChat(const std::shared_ptr<Chat>& chat) const; /*Finds index in the _chat_array to insert new Chat*/
    int _findIndexForChat(const std::shared_ptr<Chat>& chat) const; /*Finds index in the _chat_array to insert new Chat*/

    const std::shared_ptr<Chat>& getPrivateChat(const std::shared_ptr<User>& source_user, const std::shared_ptr<User>& target_user) const;
    const std::shared_ptr<Chat>& _getPrivateChat(const std::shared_ptr<User>& source_user, const std::shared_ptr<User>& target_user) const;

    int checkingForStringExistence(const std::string& string, const std::string& (User::*get)() const) const; /*Searches for matching line*/
    int menu(std::string* string_arr, int size) const; /* string_arr{0] is Menu Name , printed with underline and without number*/
};
