#include <iostream>
#include <cassert>

#include "Application.h"
#include "Chat.h"
#include "Utils.h"
#include "User.h"

Application::Application(int user_number) : _max_user_number(user_number), _max_chat_number(_max_user_number * _max_user_number)
{
    assert(user_number && "User number must be greater than 0!");

    _user_array = new User*[_max_user_number];
    _chat_array = new Chat*[_max_chat_number];        // TODO _user_number * _user_number ?
    _chat_array[0] = new Chat(MAX_MESSAGES_IN_CHAT);  // _chat_array[0] allways Common Chat
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
        std::cout << "Name(max " << MAX_INPUT_SIZE << " letters):";
        Utils::getBoundedString(user_name, MAX_INPUT_SIZE);
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
    return ++_current_user_number;
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
    std::cout <<  "Password:";
    while (!isOK)
    {
        Utils::getBoundedString(user_password, MAX_INPUT_SIZE, true);
        if (_user_array[index]->getUserPassword() != user_password)
        {
            std::cout << "Password don't match!" << std::endl;
            std::cout << std::endl << "Try again?(Y/N):";
            if (!Utils::isOKSelect()) return UNSUCCESSFUL;
            continue;
        }
        std::cout << std::endl << std::endl;
        isOK = true;
    }
    //   _current_user = _user_array[index];

    selectCommonOrPrivate(_user_array[index]);

    return index;
}

int Application::selectCommonOrPrivate(User* user)
{
    bool isContinue = true;
    while (isContinue)
    {
        std::cout << "1.Common chat" << std::endl;
        std::cout << "2.Private chat" << std::endl;
        std::cout << "3.Sign Out" << std::endl;

        int res{Utils::getValue()};

        switch (res)
        {
            case 1: commonChat(user); break;
            case 2: privateMenu(user); break;
            default: isContinue = false; break;
        }
    }

    return 0;
}

int Application::commonChat(User* user) const
{
    bool isContinue = true;
    while (isContinue)
    {
        std::cout << "1.View chat" << std::endl;
        std::cout << "2.Add message" << std::endl;
        std::cout << "3.Edit message" << std::endl;
        std::cout << "4.Delete message" << std::endl;
        std::cout << "5.Exit" << std::endl;

        int res{Utils::getValue()};

        switch (res)
        {
            case 1: _chat_array[0]->printMessages(0, _chat_array[0]->getCurrentMessageNum()); break;
            case 2: _chat_array[0]->addMessage(*user); break;
            case 3:
            {
                std::cout << "Select message number for editing: ";
                int message_number{Utils::getValue()};
                _chat_array[0]->editMessage(message_number);
            }
            break;
            case 4:
            {
                std::cout << "Select message number for deleting: ";
                int message_number{Utils::getValue()};
                _chat_array[0]->deleteMessage(message_number);
            }
            break;
            default: isContinue = false; break;
        }
    }

    return 0;
}

int Application::privateMenu(User* user)
{
    bool isContinue = true;
    while (isContinue)
    {
        std::cout << std::endl << "1.View chat users names" << std::endl;
        std::cout << "2.Select target user name" << std::endl;
        std::cout << "3.Exit" << std::endl;

        int res{Utils::getValue()};
        switch (res)
        {
            case 1:
            {
                for (auto i{0}; i < _current_user_number; ++i)
                {
                    std::cout << i << "." << _user_array[i]->getUserName() << std::endl;
                    if (!((i + 1) % LINE_TO_PAGE)) std::cin.get();
                }
            };
            break;
            case 2:
            {

                auto index{-1};
                bool isOK = false;
                while (!isOK)
                {
                    std::cout << "Input target user name:";
                    std::string user_name;
                    std::cin >> user_name;
                    const std::string& (User::*get_name)() const = &User::getUserName;
                    if ((index = checkingForStringExistence(user_name, get_name)) == UNSUCCESSFUL)
                    {
                        std::cout << "User don't exist!" << std::endl;
                        std::cout << std::endl << "Try again?(Y/N):";
                        if (!Utils::isOKSelect()) break;
                        continue;
                    }
                    isOK = true;
                }
                privateChat(user, _user_array[index]);
            }
            break;
            default: isContinue = false; break;
        }
    }
    return 0;
}

int Application::privateChat(User* source_user, User* target_user)
{
    auto isContinue{true};

    auto currentChat{getPrivateChat(source_user, target_user)};

    while (isContinue)
    {
        std::cout << "1.View chat" << std::endl;
        std::cout << "2.Add message" << std::endl;
        std::cout << "3.Edit message" << std::endl;
        std::cout << "4.Delete message" << std::endl;
        std::cout << "5.Exit" << std::endl;

        int res{Utils::getValue()};

        switch (res)
        {
            case 1:
                if (currentChat) currentChat->printMessages(0, currentChat->getCurrentMessageNum());
                break;
            case 2:
                if (!currentChat)
                {
                    currentChat = new Chat(MAX_MESSAGES_IN_CHAT);
                    auto first_user{source_user->getUserID()};
                    auto second_user{target_user->getUserID()};
                    auto isSwap(Utils::minToMaxOrder(first_user, second_user));

                    if (isSwap)
                    {
                        currentChat->setFirstUser(target_user);
                        currentChat->setSecondUser(source_user);
                    }
                    else
                    {
                        currentChat->setFirstUser(source_user);
                        currentChat->setSecondUser(target_user);
                    }
                }
                currentChat->addMessage(*source_user);

                 //_chat_array[++_current_chat_number] =

                break;
            case 3:
            {
                std::cout << "Select message number for editing: ";
                int message_number{Utils::getValue()};
                if(currentChat) currentChat->editMessage(message_number);
            }
            break;
            case 4:
            {
                std::cout << "Select message number for deleting: ";
                int message_number{Utils::getValue()};
                if (currentChat) currentChat->deleteMessage(message_number);
            }
            break;
            default: isContinue = false; break;
        }
    }
    return 0;
}

Chat* Application::getPrivateChat(User* source_user, User* target_user) const
{
    auto first_user{source_user->getUserID()};
    auto second_user{target_user->getUserID()};

    Utils::minToMaxOrder(first_user, second_user);

    for (auto i{1}; i < _current_chat_number; ++i)
    {
        if (_chat_array[i]->getFirstUser()->getUserID() != first_user) continue;
        if (_chat_array[i]->getSecondUser()->getUserID() != second_user) continue;
        return _chat_array[i];
    }
    return nullptr;
}

int Application::checkingForStringExistence(const std::string& string, const std::string& (User::*get)() const) const
{
    for (auto i{0}; i < _current_user_number; ++i)
    {
        if (string == (_user_array[i]->*get)()) return i;
    }
    return UNSUCCESSFUL;
}
