#include <iostream>
#include <cassert>

#include "Application.h"
#include "Chat.h"
#include "Utils.h"
#include "User.h"

Application::Application()
{
    _chat_array.insertBefore(
        std::make_shared<Chat>(), 0);  //    [0] = std::make_shared<Chat>(MAX_MESSAGES_IN_CHAT);  // _chat_array[0] allways Common Chat
}

void Application::run()
{
    std::cout << BOLDYELLOW << UNDER_LINE << "Wellcome to Console Chat!" << RESET << std::endl;

    bool isContinue = true;
    while (isContinue)
    {
        std::cout << std::endl;
        std::cout << BOLDGREEN << "1." << RESET << "Sign In" << std::endl;
        std::cout << BOLDGREEN << "2." << RESET << "Create account" << std::endl;
        std::cout << BOLDGREEN << "3." << RESET << "Quit" << std::endl;
        std::cout << YELLOW << "Your choice?: " << BOLDGREEN;
        int res{Utils::getValue()};
        std::cout << RESET;

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
    std::cout << std::endl;
    std::cout << BOLDYELLOW << UNDER_LINE << "Create account:" << RESET << std::endl;
    while (!isOK)
    {
        std::cout << "Name(max " << MAX_INPUT_SIZE << " letters):";
        std::cout << BOLDGREEN;
        Utils::getBoundedString(user_name, MAX_INPUT_SIZE);
        std::cout << RESET;
        const std::string& (User::*get_name)() const = &User::getUserName;
        if (checkingForStringExistence(user_name, get_name) != UNSUCCESSFUL)
        {
            std::cout << std::endl << RED << "Please change name!" << RESET << std::endl;
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
        std::cout << BOLDGREEN;
        Utils::getBoundedString(user_login, MAX_INPUT_SIZE);
        std::cout << RESET;
        const std::string& (User::*get_login)() const = &User::getUserLogin;
        if (checkingForStringExistence(user_login, get_login) != UNSUCCESSFUL)
        {
            std::cout << std::endl << RED << "Please change login." << RESET ;
        }
        else
        {
            isOK = true;
        }
    }

    std::cout << std::endl << "Password(max " << MAX_INPUT_SIZE << " letters):";
    std::string user_password;
    std::cout << BOLDGREEN;
    Utils::getBoundedString(user_password, MAX_INPUT_SIZE, true);
    std::cout << RESET;

    std::cout << BOLDYELLOW << std::endl << "Create account?(Y/N): " << BOLDGREEN;
    if (!Utils::isOKSelect()) return UNSUCCESSFUL;

    _user_array.insertBefore(std::make_shared<User>(user_name, user_login, user_password, _current_user_number), _current_user_number);
    return ++_current_user_number;
}

int Application::signIn()
{
    std::cout << std::endl;
    std::cout << "Sign In:" << std::endl;

    std::string user_login{};
    auto index{-1};
    bool isOK = false;
    while (!isOK)
    {
        std::cout << "Login:";
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
    while (!isOK)
    {
        std::cout << "Password:";
        Utils::getBoundedString(user_password, MAX_INPUT_SIZE, true);
        if (_user_array[index]->getUserPassword() != user_password)
        {
            std::cout << std::endl << "Password don't match!" << std::endl;
            std::cout << std::endl << "Try again?(Y/N):";
            if (!Utils::isOKSelect()) return UNSUCCESSFUL;
            continue;
        }
        std::cout << std::endl;
        isOK = true;
    }

    selectCommonOrPrivate(_user_array[index]);

    return index;
}

int Application::selectCommonOrPrivate(std::shared_ptr<User> user)
{
    bool isContinue = true;
    while (isContinue)
    {
        std::cout << std::endl;
        std::cout << "Select chat type:" << std::endl;
        std::cout << "1.Common chat" << std::endl;
        std::cout << "2.Private chat" << std::endl;
        std::cout << "3.Sign Out" << std::endl;
        std::cout << "Your choice?: ";

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

int Application::commonChat(std::shared_ptr<User> user) const
{
    bool isContinue = true;
    while (isContinue)
    {
        std::cout << std::endl;
        std::cout << "Common Chat" << std::endl;
        std::cout << "1.View chat" << std::endl;
        std::cout << "2.Add message" << std::endl;
        std::cout << "3.Edit message" << std::endl;
        std::cout << "4.Delete message" << std::endl;
        std::cout << "5.Exit" << std::endl;
        std::cout << "Your choice?: ";

        int res{Utils::getValue()};

        switch (res)
        {
            case 1:
                std::cout << std::endl;
                _chat_array[0]->printMessages(0, _chat_array[0]->getCurrentMessageNum());
                break;
            case 2: _chat_array[0]->addMessage(user); break;
            case 3:
            {
                std::cout << std::endl << "Select message number for editing: ";
                int message_number{Utils::getValue()};
                _chat_array[0]->editMessage(user, message_number - 1);  // array's indices begin from 0, Output indices begin from 1
            }
            break;
            case 4:
            {
                std::cout << std::endl << "Select message number for deleting: ";
                int message_number{Utils::getValue()};
                _chat_array[0]->deleteMessage(user, message_number - 1);  // array's indices begin from 0, Output indices begin from 1
            }
            break;
            default: isContinue = false; break;
        }
    }

    return 0;
}

int Application::privateMenu(std::shared_ptr<User> user)
{
    bool isContinue = true;
    while (isContinue)
    {
        std::cout << std::endl;
        std::cout << "Private Chat" << std::endl;
        std::cout << "1.View chat users names" << std::endl;
        std::cout << "2.Select target user name" << std::endl;
        std::cout << "3.Exit" << std::endl;
        std::cout << "Your choice?: ";

        int res{Utils::getValue()};
        switch (res)
        {
            case 1:
            {
                std::cout << std::endl;
                for (auto i{0}; i < _current_user_number; ++i)
                {
                    std::cout << i + 1 << "." << _user_array[i]->getUserName()
                              << std::endl;                         // array's indices begin from 0, Output indices begin from 1
                    if (!((i + 1) % LINE_TO_PAGE)) std::cin.get();  //  Suspend via LINE_TO_PAGE lines
                }
            };
            break;
            case 2:
            {

                auto index{-1};
                bool isOK = false;
                while (!isOK)
                {
                    std::cout << std::endl << "Input target user name:";
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

int Application::privateChat(std::shared_ptr<User> source_user, std::shared_ptr<User> target_user)
{
    auto isContinue{true};

    auto currentChat{getPrivateChat(source_user, target_user)};

    while (isContinue)
    {
        std::cout << std::endl;
        std::cout << "Private Chat" << std::endl;
        std::cout << "1.View chat" << std::endl;
        std::cout << "2.Add message" << std::endl;
        std::cout << "3.Edit message" << std::endl;
        std::cout << "4.Delete message" << std::endl;
        std::cout << "5.Exit" << std::endl;
        std::cout << "Your choice?: ";

        int res{Utils::getValue()};

        switch (res)
        {
            case 1:
                if (currentChat)
                {
                    std::cout << std::endl;
                    currentChat->printMessages(0, currentChat->getCurrentMessageNum());
                }
                break;
            case 2:
                if (!currentChat)
                {
                    currentChat = std::make_shared<Chat>();
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
                    _chat_array.insertBefore(currentChat, findIndexForChat(currentChat));
                    ++_current_chat_number;
                }
                currentChat->addMessage(source_user);
                break;
            case 3:
            {
                std::cout << std::endl << "Select message number for editing: ";
                int message_number{Utils::getValue()};
                if (currentChat)
                    currentChat->editMessage(source_user, message_number - 1);  // array's indices begin from 0, Output indices begin from 1
            }
            break;
            case 4:
            {
                std::cout << std::endl << "Select message number for deleting: ";
                int message_number{Utils::getValue()};
                if (currentChat)
                    currentChat->deleteMessage(
                        source_user, message_number - 1);  // array's indices begin from 0, Output indices begin from 1
            }
            break;
            default: isContinue = false; break;
        }
    }
    return 0;
}

int Application::findIndexForChat(std::shared_ptr<Chat> chat) const
{
    auto index{1};  // _chat_array[0] - Allways Common_Chat
    auto i{1};
    for (; i < _current_chat_number; ++i)
    {
        if (chat->getFirstUser()->getUserID() > _chat_array[i]->getFirstUser()->getUserID()) continue;
        if (chat->getSecondUser()->getUserID() > _chat_array[i]->getSecondUser()->getUserID()) continue;
        return i;  //
    }
    return i;
}

std::shared_ptr<Chat> Application::getPrivateChat(std::shared_ptr<User> source_user, std::shared_ptr<User> target_user) const
{
    auto first_user{source_user->getUserID()};
    auto second_user{target_user->getUserID()};

    Utils::minToMaxOrder(first_user, second_user);

    for (auto i{1}; i < _current_chat_number; ++i)  // _chat_array[0] - Allways Common_Chat
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
        if (string == (_user_array[i].get()->*get)()) return i;
    }
    return UNSUCCESSFUL;
}
