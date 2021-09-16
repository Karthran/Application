#include <iostream>
#include <cassert>
#include <iomanip>

#include "Application.h"
#include "Chat.h"
#include "Utils.h"
#include "User.h"
#include "BadException.h"

Application::Application()
{
    _chat_array.insertBefore(std::make_shared<Chat>(), 0);  // _chat_array[0] allways Common Chat
}

void Application::run()
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

int Application::createAccount()
{
    std::string user_name{};
    createAccount_inputName(user_name);

    std::string user_login;
    createAccount_inputLogin(user_login);

    std::string user_password;
    createAccount_inputPassword(user_password);

    std::cout << BOLDYELLOW << std::endl << "Create account?(Y/N): " << BOLDGREEN;
    if (!Utils::isOKSelect()) return UNSUCCESSFUL;

    try
    {
        _user_array.insertBefore(std::make_shared<User>(user_name, user_login, user_password, _current_user_number), _current_user_number);
        return ++_current_user_number;
    }
    catch (std::exception& e)
    {
        std::cout << BOLDRED << e.what() << RESET << std::endl;
    }
    return UNSUCCESSFUL;
}

void Application::createAccount_inputName(std::string& user_name) const
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
        if (checkingForStringExistence(user_name, get_name) != UNSUCCESSFUL)
        {
            std::cout << std::endl << RED << "Please change name!" << RESET << std::endl;
        }
        else
        {
            isOK = true;
        }
    }
}

void Application::createAccount_inputLogin(std::string& user_login) const
{
    auto isOK{false};

    while (!isOK)
    {
        std::cout << std::endl << "Login(max " << MAX_INPUT_SIZE << " letters): ";
        std::cout << BOLDGREEN;
        Utils::getBoundedString(user_login, MAX_INPUT_SIZE);
        std::cout << RESET;
        const std::string& (User::*get_login)() const = &User::getUserLogin;
        if (checkingForStringExistence(user_login, get_login) != UNSUCCESSFUL)
        {
            std::cout << std::endl << RED << "Please change login." << RESET;
        }
        else
        {
            isOK = true;
        }
    }
}

void Application::createAccount_inputPassword(std::string& user_password) const
{
    auto isOK{false};
    while (!isOK)
    {
        std::cout << std::endl << "Password(max " << MAX_INPUT_SIZE << " letters): ";
        std::cout << BOLDGREEN;
        Utils::getBoundedString(user_password, MAX_INPUT_SIZE, true);
        std::cout << RESET;

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

int Application::signIn()
{
    std::cout << std::endl;
    std::cout << BOLDYELLOW << UNDER_LINE << "Sign In:" << RESET << std::endl;

    std::string user_login{};
    auto index{signIn_inputLogin(user_login)};

    if (index == UNSUCCESSFUL) return UNSUCCESSFUL;

    std::string user_password{};
    if (signIn_inputPassword(user_password, index) == UNSUCCESSFUL) return UNSUCCESSFUL;

    selectCommonOrPrivate(_user_array[index]);

    return index;
}

int Application::signIn_inputLogin(std::string& user_login) const
{
    auto index{UNSUCCESSFUL};
    auto isOK{false};
    while (!isOK)
    {
        std::cout << RESET << "Login:";
        std::cout << BOLDGREEN;
        std::cin >> user_login;
        std::cout << RESET;
        const std::string& (User::*get_login)() const = &User::getUserLogin;
        if ((index = checkingForStringExistence(user_login, get_login)) == UNSUCCESSFUL)
        {
            std::cout << RED << "Login don't exist!" << std::endl;
            std::cout << BOLDYELLOW << std::endl << "Try again?(Y/N):" << BOLDGREEN;
            if (!Utils::isOKSelect()) return UNSUCCESSFUL;
            continue;
        }
        isOK = true;
    }
    return index;
}

int Application::signIn_inputPassword(std::string& user_password, int index) const
{
    auto isOK{false};
    while (!isOK)
    {
        std::cout << RESET << "Password:";
        std::cout << BOLDGREEN;
        Utils::getBoundedString(user_password, MAX_INPUT_SIZE, true);
        std::cout << RESET;
        if (_user_array[index]->getUserPassword() != user_password)
        {
            std::cout << std::endl << RED << "Password don't match!" << std::endl;
            std::cout << BOLDYELLOW << std::endl << "Try again?(Y/N):" << BOLDGREEN;
            if (!Utils::isOKSelect()) return UNSUCCESSFUL;
            continue;
        }
        std::cout << std::endl;
        isOK = true;
    }
    return SUCCESSFUL;
}

int Application::selectCommonOrPrivate(const std::shared_ptr<User>& user)
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

int Application::commonChat(const std::shared_ptr<User>& user) const
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
                _chat_array[0]->printMessages(0, _chat_array[0]->getCurrentMessageNum());
                break;
            case 2: commonChat_addMessage(user); break;
            case 3: commonChat_editMessage(user); break;
            case 4: commonChat_deleteMessage(user); break;
            default: isContinue = false; break;
        }
    }
    return SUCCESSFUL;
}

void Application::commonChat_addMessage(const std::shared_ptr<User>& user) const
{
    try
    {
        _chat_array[0]->addMessage(user);
    }
    catch (std::exception& e)
    {
        std::cout << BOLDRED << e.what() << RESET << std::endl;
    }
}

void Application::commonChat_editMessage(const std::shared_ptr<User>& user) const
{
    std::cout << std::endl << YELLOW << "Select message number for editing: " << BOLDGREEN;
    int message_number{Utils::getValue()};
    std::cout << RESET;
    try
    {
        _chat_array[0]->editMessage(user, message_number - 1);  // array's indices begin from 0, Output indices begin from 1
    }
    catch (std::exception& e)
    {
        std::cout << BOLDRED << e.what() << RESET << std::endl;
    }
}

void Application::commonChat_deleteMessage(const std::shared_ptr<User>& user) const
{
    std::cout << std::endl << YELLOW << "Select message number for deleting: " << BOLDGREEN;
    int message_number{Utils::getValue()};
    std::cout << RESET;
    try
    {
        _chat_array[0]->deleteMessage(user, message_number - 1);  // array's indices begin from 0, Output indices begin from 1
    }
    catch (std::exception& e)
    {
        std::cout << BOLDRED << e.what() << RESET << std::endl;
    }
}

int Application::privateMenu(const std::shared_ptr<User>& user)
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

void Application::privateMenu_viewUsersNames() const
{
    std::cout << std::endl;
    std::cout << BOLDGREEN << std::setw(5) << std::setfill(' ') << std::right << "ID"
              << "." << BOLDYELLOW << std::setw(MAX_INPUT_SIZE) << std::setfill(' ') << std::left << "User Name" << std::endl;

    for (auto i{0}; i < _current_user_number; ++i)
    {
        std::cout << BOLDGREEN << std::setw(5) << std::setfill(' ') << std::right << i + 1 << "." << BOLDYELLOW << std::setw(MAX_INPUT_SIZE)
                  << std::setfill(' ') << std::left << _user_array[i]->getUserName()
                  << std::endl;                         // array's indices begin from 0, Output indices begin from 1
        if (!((i + 1) % LINE_TO_PAGE)) std::cin.get();  //  Suspend via LINE_TO_PAGE lines
    }
    std::cout << RESET;
}
int Application::privateMenu_selectByName(const std::shared_ptr<User>& user) const
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
void Application::privateMenu_selectByID(const std::shared_ptr<User>& user)
{
    std::cout << std::endl << RESET << YELLOW << "Input target user ID: " << BOLDGREEN;
    auto index{Utils::getValue()};
    std::cout << RESET;
    try
    {
        privateChat(user, _user_array[index - 1]);  // array's indices begin from 0, Output indices begin from 1
    }
    catch (std::exception& e)
    {
        std::cout << BOLDRED << e.what() << RESET << std::endl;
    }
}

int Application::privateChat(const std::shared_ptr<User>& source_user, const std::shared_ptr<User>& target_user)
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

void Application::privateChat_addMessage(
    const std::shared_ptr<User>& source_user, const std::shared_ptr<User>& target_user, std::shared_ptr<Chat>& chat)
{
    if (!chat)
    {
        chat = std::make_shared<Chat>();
        auto first_user{source_user->getUserID()};
        auto second_user{target_user->getUserID()};
        auto isSwap(Utils::minToMaxOrder(first_user, second_user));

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
        try
        {
            _chat_array.insertBefore(chat, findIndexForChat(chat));
            ++_current_chat_number;
        }
        catch (std::exception& e)
        {
            std::cout << BOLDRED << e.what() << RESET << std::endl;
        }
    }
    chat->addMessage(source_user);
}
void Application::privateChat_editMessage(
    const std::shared_ptr<User>& source_user, const std::shared_ptr<User>& target_user, const std::shared_ptr<Chat>& chat) const
{
    std::cout << std::endl << RESET << YELLOW << "Select message number for editing: " << BOLDGREEN;
    int message_number{Utils::getValue()};
    std::cout << RESET;
    if (chat) try
        {
            chat->editMessage(source_user, message_number - 1);  // array's indices begin from 0, Output indices begin from 1
        }
        catch (std::exception& e)
        {
            std::cout << BOLDRED << e.what() << RESET << std::endl;
        }
}

void Application::privateChat_deleteMessage(
    const std::shared_ptr<User>& source_user, const std::shared_ptr<User>& target_user, const std::shared_ptr<Chat>& chat) const
{
    std::cout << std::endl << RESET << YELLOW << "Select message number for deleting: " << BOLDGREEN;
    int message_number{Utils::getValue()};
    std::cout << RESET;
    if (chat) try
        {

            chat->deleteMessage(source_user, message_number - 1);  // array's indices begin from 0, Output indices begin from 1
        }
        catch (std::exception& e)
        {
            std::cout << BOLDRED << e.what() << RESET << std::endl;
        }
}

int Application::findIndexForChat(const std::shared_ptr<Chat>& chat) const
{
    auto i{1};  // _chat_array[0] - Allways Common_Chat
    for (; i < _current_chat_number; ++i)
    {
        if (chat->getFirstUser()->getUserID() > _chat_array[i]->getFirstUser()->getUserID()) continue;
        if (chat->getFirstUser()->getUserID() < _chat_array[i]->getFirstUser()->getUserID()) return i;
        if (chat->getSecondUser()->getUserID() > _chat_array[i]->getSecondUser()->getUserID()) continue;
        return i;
    }
    return i;
}

int Application::_findIndexForChat(const std::shared_ptr<Chat>& chat) const
{
    auto first_userID{chat->getFirstUser()->getUserID()};
    auto second_userID{chat->getSecondUser()->getUserID()};

    auto isContinue(true);
    auto start{0};
    auto stop{_current_chat_number - 1};
    auto middle{0};

    while (isContinue)
    {
        middle = (start + stop) / 2;
        auto fu_sgn{sign(first_userID - _chat_array[middle]->getFirstUser()->getUserID())};
        switch (fu_sgn)
        {
            case -1: stop = middle; break;
            case 0:
            {
                auto su_sgn{sign(second_userID - _chat_array[middle]->getSecondUser()->getUserID())};
                switch (su_sgn)
                {
                    case -1: stop = middle; break;
                    case 0:
                    {
                        return middle;
                    }
                    break;
                    case 1:
                        if (second_userID < _chat_array[middle + 1]->getSecondUser()->getUserID()) return middle + 1;
                        start = middle;
                        break;
                }
            }
            break;
            case 1:
                if (first_userID < _chat_array[middle + 1]->getFirstUser()->getUserID()) return middle + 1;
                start = middle;
                break;
            default: break;
        }
    }
    return 0;
}

const std::shared_ptr<Chat>& Application::getPrivateChat(
    const std::shared_ptr<User>& source_user, const std::shared_ptr<User>& target_user) const
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

const std::shared_ptr<Chat>& Application::_getPrivateChat(
    const std::shared_ptr<User>& source_user, const std::shared_ptr<User>& target_user) const
{
    auto first_userID{source_user->getUserID()};
    auto second_userID{target_user->getUserID()};
    Utils::minToMaxOrder(first_userID, second_userID);

    auto isContinue(true);
    auto start{0};
    auto stop{_current_chat_number - 1};
    auto middle{0};

    while (isContinue)
    {
        middle = (start + stop) / 2;
        auto fu_sgn{sign(first_userID - _chat_array[middle]->getFirstUser()->getUserID())};
        switch (fu_sgn)
        {
            case -1: stop = middle; break;
            case 0:
            {
                auto su_sgn{sign(second_userID - _chat_array[middle]->getSecondUser()->getUserID())};
                switch (su_sgn)
                {
                    case -1: stop = middle; break;
                    case 0:
                    {
                        return _chat_array[middle];
                    }
                    break;
                    case 1: start = middle; break;
                }
            }
            break;
            case 1: start = middle; break;
            default: break;
        }
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

int Application::menu(std::string* string_arr, int size) const
{
    if (size <= 0) return UNSUCCESSFUL;

    std::cout << std::endl;
    std::cout << BOLDYELLOW << UNDER_LINE << string_arr[0] << RESET << std::endl;  // index 0 is Menu Name

    for (auto i{1}; i < size; ++i)
    {
        std::cout << BOLDGREEN << i << "." << RESET << string_arr[i] << std::endl;
    }
    std::cout << YELLOW << "Your choice?: " << BOLDGREEN;
    int menu_item{Utils::getValue()};
    std::cout << RESET;

    return menu_item;
}
