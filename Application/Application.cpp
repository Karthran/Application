#include <iostream>

#include "Application.h"
#include "Chat.h"
#include "Utils.h"

Application::Application(int user_number) : _user_number(user_number), _max_chat_number(_user_number * _user_number)
{

    _chat_array = new Chat*[_max_chat_number];// TODO _user_number * _user_number ?
}

Application::~Application()
{
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
            case 1: 
                signIn(); 
                break;
            case 2:
                createAccount();
                break;
            default:
                isContinue = false;
                break;
        }
    }
}

int Application::createAccount()
{
    std::cout << "Name:";
    Utils::getBoundedString(MAX_INPUT_SIZE);

    std::cout << "Login:";
    Utils::getBoundedString(MAX_INPUT_SIZE);

    std::cout << "Password:";
    Utils::getBoundedString(MAX_INPUT_SIZE);

    return 0;
}

int Application::signIn()
{
    return 0;
}
