﻿#include <iostream>
#include <cassert>
#include <iomanip>
#include <exception>

#include "Application.h"
#include "Chat.h"
#include "Utils.h"
#include "User.h"
#include "BadException.h"
#include "SHA1.h"

Application::Application()
{
    _common_chat = std::make_shared<Chat>();
}

auto Application::run() -> void
{
    std::cout << BOLDYELLOW << UNDER_LINE << "Wellcome to Console Chat!" << RESET << std::endl;

    auto isContinue{true};
    while (isContinue)
    {
        std::string menu_arr[]{"Main menu:", "Sign In", "Create account", "Quit"};

        auto menu_item{menu(menu_arr, 4)};

        switch (menu_item)
        {
            case 1: signIn(); break;
            case 2: createAccount(); break;
            default: isContinue = false; break;
        }
    }
}

auto Application::createAccount() -> int
{
    std::string user_name{};
    createAccount_inputName(user_name);

    std::string user_login;
    createAccount_inputLogin(user_login);

    std::string user_password;
    createAccount_inputPassword(user_password);

    std::cout << BOLDYELLOW << std::endl << "Create account?(Y/N): " << BOLDGREEN;
    if (!Utils::isOKSelect()) return UNSUCCESSFUL;

    _user_array.push_back(std::make_shared<User>(user_name, user_login, _current_user_number));

    std::shared_ptr<uint[]> hash = sha1(user_password);
    _password_hash[user_login] = hash;

    return ++_current_user_number;
}

auto Application::createAccount_inputName(std::string& user_name) const -> void
{
    std::cout << std::endl;
    std::cout << BOLDYELLOW << UNDER_LINE << "Create account:" << RESET << std::endl;
    auto isOK{false};
    while (!isOK)
    {
        std::cout << "Name(max " << MAX_INPUT_SIZE << " letters): ";
        std::cout << BOLDGREEN;
        Utils::getBoundedString(user_name, MAX_INPUT_SIZE);
        std::cout << RESET;
        const std::string& (User::*get_name)() const = &User::getUserName;
        if (user_name.empty() || checkingForStringExistence(user_name, get_name) != UNSUCCESSFUL)
        {
            std::cout << std::endl << RED << "Please change name!" << RESET << std::endl;
        }
        else
        {
            isOK = true;
        }
    }
}

auto Application::createAccount_inputLogin(std::string& user_login) const -> void
{
    auto isOK{false};

    while (!isOK)
    {
        std::cout << std::endl << "Login(max " << MAX_INPUT_SIZE << " letters): ";
        std::cout << BOLDGREEN;
        Utils::getBoundedString(user_login, MAX_INPUT_SIZE);
        std::cout << RESET;
        const std::string& (User::*get_login)() const = &User::getUserLogin;
        if (user_login.empty() || checkingForStringExistence(user_login, get_login) != UNSUCCESSFUL)
        {
            std::cout << std::endl << RED << "Please change login." << RESET;
        }
        else
        {
            isOK = true;
        }
    }
}

auto Application::createAccount_inputPassword(std::string& user_password) const -> void
{
    auto isOK{false};
    while (!isOK)
    {
        std::cout << std::endl << "Password(max " << MAX_INPUT_SIZE << " letters): ";
        std::cout << BOLDGREEN;
        Utils::getBoundedString(user_password, MAX_INPUT_SIZE, true);
        std::cout << RESET;

        if (user_password.empty()) continue;

        std::cout << std::endl << "Re-enter your password: ";
        std::cout << BOLDGREEN;

        std::string check_user_password;
        Utils::getBoundedString(check_user_password, MAX_INPUT_SIZE, true);
        std::cout << RESET;
        if (user_password != check_user_password)
        {
            std::cout << std::endl << RED << "Password don't match!" << RESET;
        }
        else
        {
            isOK = true;
        }
    }
}

auto Application::signIn() -> int
{
    std::cout << std::endl;
    std::cout << BOLDYELLOW << UNDER_LINE << "Sign In:" << RESET << std::endl;

    std::string user_login{};
    std::string user_password{};
    while (true)
    {
        auto index{signIn_inputLogin(user_login)};

        signIn_inputPassword(user_password);

        if (index != UNSUCCESSFUL)
        {
            auto it = _password_hash.find(user_login);
            std::shared_ptr<uint[]> hash = sha1(user_password);
            auto password_match{true};
            for (auto i{0}; i < SHA1HASHLENGTHUINTS; ++i)
            {
                if (it->second[i] == hash[i]) continue;
                password_match = false;
                break;
            }
            if (password_match)
            {
                selectCommonOrPrivate(_user_array[index]);
                return index;
            }
        }

        std::cout << std::endl << RED << "Login or Password don't match!" << std::endl;
        std::cout << BOLDYELLOW << std::endl << "Try again?(Y/N):" << BOLDGREEN;
        if (!Utils::isOKSelect()) return UNSUCCESSFUL;
    }
}

auto Application::signIn_inputLogin(std::string& user_login) const -> int
{
    std::cout << RESET << "Login:";
    std::cout << BOLDGREEN;
    std::cin >> user_login;
    std::cout << RESET;
    const std::string& (User::*get_login)() const = &User::getUserLogin;
    return checkingForStringExistence(user_login, get_login);
}
auto Application::signIn_inputPassword(std::string& user_password) const -> void
{
    std::cout << RESET << "Password:";
    std::cout << BOLDGREEN;
    Utils::getBoundedString(user_password, MAX_INPUT_SIZE, true);
    std::cout << RESET;
}

auto Application::selectCommonOrPrivate(const std::shared_ptr<User>& user) -> int
{
    auto isContinue{true};
    while (isContinue)
    {
        std::string menu_arr[] = {"Select chat type:", "Common chat", "Private chat", "Sign Out"};

        auto menu_item{menu(menu_arr, 4)};

        switch (menu_item)
        {
            case 1: commonChat(user); break;
            case 2: privateMenu(user); break;
            default: isContinue = false; break;
        }
    }

    return 0;
}

auto Application::commonChat(const std::shared_ptr<User>& user) const -> int
{
    auto isContinue{true};
    while (isContinue)
    {
        std::string menu_arr[]{"Common Chat:", "View chat", "Add message", "Edit message", "Delete message", "Exit"};
        auto menu_item{menu(menu_arr, 6)};

        switch (menu_item)
        {
            case 1:
                std::cout << std::endl;
                _common_chat->printMessages(0, _common_chat->getCurrentMessageNum());
                break;
            case 2: commonChat_addMessage(user); break;
            case 3: commonChat_editMessage(user); break;
            case 4: commonChat_deleteMessage(user); break;
            default: isContinue = false; break;
        }
    }
    return SUCCESSFUL;
}

auto Application::commonChat_addMessage(const std::shared_ptr<User>& user) const -> void
{
    _common_chat->addMessage(user);
}

auto Application::commonChat_editMessage(const std::shared_ptr<User>& user) const -> void
{
    std::cout << std::endl << YELLOW << "Select message number for editing: " << BOLDGREEN;
    int message_number{Utils::inputIntegerValue()};
    std::cout << RESET;
    _common_chat->editMessage(user, message_number - 1);  // array's indices begin from 0, Output indices begin from 1
}

auto Application::commonChat_deleteMessage(const std::shared_ptr<User>& user) const -> void
{
    std::cout << std::endl << YELLOW << "Select message number for deleting: " << BOLDGREEN;
    int message_number{Utils::inputIntegerValue()};
    std::cout << RESET;
    _common_chat->deleteMessage(user, message_number - 1);  // array's indices begin from 0, Output indices begin from 1
}

auto Application::privateMenu(const std::shared_ptr<User>& user) -> int
{
    auto isContinue{true};
    while (isContinue)
    {
        std::string menu_arr[]{"Private Chat:", "View chat users names", "Select target user by name", "Select target user by ID", "Exit"};

        auto menu_item{menu(menu_arr, 5)};

        switch (menu_item)
        {
            case 1: privateMenu_viewUsersNames(); break;
            case 2:
            {
                auto index{0};
                if ((index = privateMenu_selectByName(user)) != UNSUCCESSFUL) privateChat(user, _user_array[index]);
            }
            break;
            case 3: privateMenu_selectByID(user); break;
            default: isContinue = false; break;
        }
    }
    return 0;
}

auto Application::privateMenu_viewUsersNames() const -> void
{
    std::cout << std::endl;
    std::cout << BOLDGREEN << std::setw(5) << std::setfill(' ') << std::right << "ID"
              << "." << BOLDYELLOW << std::setw(MAX_INPUT_SIZE) << std::setfill(' ') << std::left << "User Name" << std::endl;

    for (auto i{0}; i < _current_user_number; ++i)
    {
        std::cout << BOLDGREEN << std::setw(5) << std::setfill(' ') << std::right << i + 1 << "." << BOLDYELLOW << std::setw(MAX_INPUT_SIZE)
                  << std::setfill(' ') << std::left << _user_array[i]->getUserName()
                  << std::endl;  // array's indices begin from 0, Output indices begin from 1
        if (!((i + 1) % LINE_TO_PAGE))
        {
            std::cout << std::endl << RESET << YELLOW << "Press Enter for continue...";
            std::cin.get();  //  Suspend via LINE_TO_PAGE lines
        }
    }
    std::cout << RESET;
}
auto Application::privateMenu_selectByName(const std::shared_ptr<User>& user) const -> int
{
    auto index{UNSUCCESSFUL};
    auto isOK{false};
    while (!isOK)
    {
        std::cout << std::endl << RESET << YELLOW << "Input target user name: " << BOLDYELLOW;
        std::string user_name;
        std::cin >> user_name;
        std::cout << RESET;
        const std::string& (User::*get_name)() const = &User::getUserName;
        if ((index = checkingForStringExistence(user_name, get_name)) == UNSUCCESSFUL)
        {
            std::cout << RED << "User don't exist!" << std::endl;
            std::cout << std::endl << BOLDYELLOW << "Try again?(Y/N):" << BOLDGREEN;
            if (!Utils::isOKSelect()) return UNSUCCESSFUL;
            continue;
        }
        isOK = true;
    }
    return index;
}
auto Application::privateMenu_selectByID(const std::shared_ptr<User>& user) -> void
{
    std::cout << std::endl << RESET << YELLOW << "Input target user ID: " << BOLDGREEN;
    auto index{Utils::inputIntegerValue()};
    std::cout << RESET;
    try
    {
        privateChat(user, _user_array.at(index - 1));  // array's indices begin from 0, Output indices begin from 1
    }
    catch (std::exception& e)
    {
        std::cout << BOLDRED << "Exception: " << e.what() << RESET << std::endl;
    }
}

auto Application::privateChat(const std::shared_ptr<User>& source_user, const std::shared_ptr<User>& target_user) -> int
{
    auto isContinue{true};

    auto currentChat{getPrivateChat(source_user, target_user)};

    while (isContinue)
    {
        std::string menu_arr[]{"Private Chat:", "View chat", "Add message", "Edit message", "Delete message", "Exit"};

        auto menu_item{menu(menu_arr, 6)};

        switch (menu_item)
        {
            case 1:
                if (currentChat)
                {
                    std::cout << std::endl;
                    currentChat->printMessages(0, currentChat->getCurrentMessageNum());
                }
                break;
            case 2: privateChat_addMessage(source_user, target_user, currentChat); break;
            case 3: privateChat_editMessage(source_user, target_user, currentChat); break;
            case 4: privateChat_deleteMessage(source_user, target_user, currentChat); break;
            default: isContinue = false; break;
        }
    }
    return 0;
}

auto Application::privateChat_addMessage(
    const std::shared_ptr<User>& source_user, const std::shared_ptr<User>& target_user, std::shared_ptr<Chat>& chat) -> void
{
    if (!chat)
    {
        chat = std::make_shared<Chat>();
        long long first_userID{source_user->getUserID()};
        long long second_userID{target_user->getUserID()};
        auto isSwap(Utils::minToMaxOrder(first_userID, second_userID));

        long long mapKey{(first_userID << 32) + second_userID};  // Create value for key value

        if (isSwap)
        {
            chat->setFirstUser(target_user);
            chat->setSecondUser(source_user);
        }
        else
        {
            chat->setFirstUser(source_user);
            chat->setSecondUser(target_user);
        }
        _private_chat_array[mapKey] = chat;
        ++_current_chat_number;
    }
    chat->addMessage(source_user);
}
auto Application::privateChat_editMessage(
    const std::shared_ptr<User>& source_user, const std::shared_ptr<User>& target_user, const std::shared_ptr<Chat>& chat) const -> void
{
    std::cout << std::endl << RESET << YELLOW << "Select message number for editing: " << BOLDGREEN;
    int message_number{Utils::inputIntegerValue()};
    std::cout << RESET;
    if (chat)
    {
        chat->editMessage(source_user, message_number - 1);  // array's indices begin from 0, Output indices begin from 1
    }
}

auto Application::privateChat_deleteMessage(
    const std::shared_ptr<User>& source_user, const std::shared_ptr<User>& target_user, const std::shared_ptr<Chat>& chat) const -> void
{
    std::cout << std::endl << RESET << YELLOW << "Select message number for deleting: " << BOLDGREEN;
    int message_number{Utils::inputIntegerValue()};
    std::cout << RESET;
    if (chat)
    {

        chat->deleteMessage(source_user, message_number - 1);  // array's indices begin from 0, Output indices begin from 1
    }
}

auto Application::getPrivateChat(const std::shared_ptr<User>& source_user, const std::shared_ptr<User>& target_user) const
    -> const std::shared_ptr<Chat>&
{
    long long first_userID{source_user->getUserID()};
    long long second_userID{target_user->getUserID()};

    Utils::minToMaxOrder(first_userID, second_userID);

    long long searchID{(first_userID << 32) + second_userID};  // Create value for search

    auto it = _private_chat_array.begin();

    for (; it != _private_chat_array.end(); ++it)
    {
        if (it->first == searchID) return it->second;
    }

    return std::shared_ptr<Chat>();
}

auto Application::checkingForStringExistence(const std::string& string, const std::string& (User::*get)() const) const -> int
{
    for (auto i{0}; i < _current_user_number; ++i)
    {
        if (string == (_user_array[i].get()->*get)()) return i;
    }
    return UNSUCCESSFUL;
}

auto Application::menu(std::string* string_arr, int size) const -> int
{
    if (size <= 0) return UNSUCCESSFUL;

    std::cout << std::endl;
    std::cout << BOLDYELLOW << UNDER_LINE << string_arr[0] << RESET << std::endl;  // index 0 is Menu Name

    for (auto i{1}; i < size; ++i)
    {
        std::cout << BOLDGREEN << i << "." << RESET << string_arr[i] << std::endl;
    }
    std::cout << YELLOW << "Your choice?: " << BOLDGREEN;
    int menu_item{Utils::inputIntegerValue()};
    std::cout << RESET;

    return menu_item;
}
