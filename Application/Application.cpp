#include <iostream>

#include "Application.h"
#include "Chat.h"
#include "Utils.h"
#include "User.h"

Application::Application(int user_number) : _max_user_number(user_number), _max_chat_number(_max_user_number * _max_user_number)
{
    _user_array = new User*[_max_user_number];
    _chat_array = new Chat*[_max_chat_number];  // TODO _user_number * _user_number ?
}

Application::~Application()
{
    ///////////////////////////////////////////////////////////////////////////////////
    for (auto i{0}; i < _current_user_number; ++i) 
    {
        delete _user_array[i];
    }
    ///////////////////////////////////////////////////////////////////////////////////
    delete[] _user_array;

    ///////////////////////////////////////////////////////////////////////////////////
    for (auto i{0}; i < _current_chat_number; ++i)
    {
        delete _chat_array[i];
    }
    ///////////////////////////////////////////////////////////////////////////////////
    delete[] _chat_array;
}

void Application::run()
{
    std::cout << "Wellcome to Console Chat." << std::endl;

    bool isContinue = true;
    while (isContinue)
    {
        std::cout << "1.Sign In" << std::endl;
        std::cout << "2.Create account" << std::endl;
        std::cout << "3.Quit" << std::endl;

        int res{Utils::getValue()};

        switch (res)
        {
            case 1: signIn(); break;
            case 2: createAccount(); break;
            default: isContinue = false; break;
        }
    }
}

int Application::createAccount()
{
    bool isOK = false;
    std::string user_name{};
    while (!isOK)
    {
        std::cout << "Name(max " << MAX_INPUT_SIZE  << " letters):";
        Utils::getBoundedString(user_name,MAX_INPUT_SIZE);
        const std::string& (User::*get_name)() const = &User::getUserName;
        if (checkingForStringExistence(user_name, get_name) != UNSUCCESSFUL)
        {
            std::cout << "Please change name." << std::endl;
        }
        else
        {
            isOK = true;
        }
    }

    isOK = false;
    std::string user_login;
    while (!isOK)
    {
        std::cout << std::endl << "Login(max " << MAX_INPUT_SIZE << " letters):";
        Utils::getBoundedString(user_login, MAX_INPUT_SIZE);
        const std::string& (User::*get_login)() const = &User::getUserLogin;
        if (checkingForStringExistence(user_login, get_login) != UNSUCCESSFUL)
        {
            std::cout << "Please change login." << std::endl;
        }
        else
        {
            isOK = true;
        }
    }

    std::cout << std::endl << "Password(max " << MAX_INPUT_SIZE << " letters):";
    std::string user_password;
    Utils::getBoundedString(user_password, MAX_INPUT_SIZE, true);

    std::cout << std::endl << "Create account?(Y/N):";
    if (!Utils::isOKSelect()) return UNSUCCESSFUL; 

    _user_array[_current_user_number] = new User(user_name, user_login, user_password, _current_user_number);
    return _current_user_number++;
}

int Application::signIn()
{
    std::cout << std::endl;
    std::string user_login{};
    std::cout << std::endl << "Login:";

    auto index{-1};
    bool isOK = false;
    while (!isOK)
    {
        std::cin >> user_login;
        const std::string& (User::*get_login)() const = &User::getUserLogin;
        if ((index = checkingForStringExistence(user_login, get_login)) == UNSUCCESSFUL)
        {
            std::cout << "Login don't exist!" << std::endl;
            std::cout << std::endl << "Try again?(Y/N):";
            if (!Utils::isOKSelect()) return UNSUCCESSFUL;
            continue;
        }
        isOK = true;
    }

    std::string user_password{};
    isOK = false;
    std::cout << std::endl << "Password:";
    while (!isOK)
    {
        std::cin >> user_password;
        if (_user_array[index]->getUserPassword() != user_password)
        {
            std::cout << "Password don't match!" << std::endl;
            std::cout << std::endl << "Try again?(Y/N):";
            if (!Utils::isOKSelect()) return UNSUCCESSFUL;
            continue;
        }
        isOK = true;
    }
    _current_user = _user_array[index];

    return index;
}

int Application::checkingForStringExistence(const std::string& string, const std::string& (User::*get)() const)
{
    for (auto i{0}; i < _current_user_number; ++i)
    {
        if (string == (_user_array[i]->*get)()) return i;
    }
    return UNSUCCESSFUL;
}
