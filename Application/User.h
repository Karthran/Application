#pragma once
#include <string>
class User
{
public:
    User() {}
    User(const std::string& user_name, std::string& user_login, std::string& user_password, int user_ID)
        : _user_name(user_name), _user_login(user_login), _user_password(user_password), _user_ID(user_ID)
    {
    }

    ~User() {}

    void setUserName(const std::string& name) { _user_name = name; }
    void setUserLogin(const std::string& login) { _user_login = login; }
    void setUserPassword(const std::string& password) { _user_password = password; }
    void setUserID(int id) { _user_ID = id; }

    const std::string& getUserName() const { return _user_name; }
    const std::string& getUserLogin() const { return _user_login; }
    const std::string& getUserPassword() const { return _user_password; }
    int getUserID() const { return _user_ID; }

private:
    std::string _user_name{};
    std::string _user_login{};
    std::string _user_password{};
    int _user_ID{};
};
