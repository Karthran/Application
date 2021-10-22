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

    try
    {
        _user_array.push_back(std::make_shared<User>(user_name, user_login, user_password, _current_user_number));
        return ++_current_user_number;
    }
    catch (std::exception& e)
    {
        std::cout << BOLDRED << e.what() << RESET << std::endl;
    }
    return UNSUCCESSFUL;
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
    auto index{signIn_inputLogin(user_login)};

    if (index == UNSUCCESSFUL) return UNSUCCESSFUL;

    std::string user_password{};
    if (signIn_inputPassword(user_password, index) == UNSUCCESSFUL) return UNSUCCESSFUL;

    selectCommonOrPrivate(_user_array[index]);

    return index;
}

auto Application::signIn_inputLogin(std::string& user_login) const -> int
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

auto Application::signIn_inputPassword(std::string& user_password, int index) const -> int
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
    try
    {
        _common_chat->addMessage(user);
    }
    catch (std::exception& e)
    {
        std::cout << BOLDRED << e.what() << RESET << std::endl;
    }
}

auto Application::commonChat_editMessage(const std::shared_ptr<User>& user) const -> void
{
    std::cout << std::endl << YELLOW << "Select message number for editing: " << BOLDGREEN;
    int message_number{Utils::inputIntegerValue()};
    std::cout << RESET;
    try
    {
        _common_chat->editMessage(user, message_number - 1);  // array's indices begin from 0, Output indices begin from 1
    }
    catch (std::exception& e)
    {
        std::cout << BOLDRED << e.what() << RESET << std::endl;
    }
}

auto Application::commonChat_deleteMessage(const std::shared_ptr<User>& user) const -> void
{
    std::cout << std::endl << YELLOW << "Select message number for deleting: " << BOLDGREEN;
    int message_number{Utils::inputIntegerValue()};
    std::cout << RESET;
    try
    {
        _common_chat->deleteMessage(user, message_number - 1);  // array's indices begin from 0, Output indices begin from 1
    }
    catch (std::exception& e)
    {
        std::cout << BOLDRED << e.what() << RESET << std::endl;
    }
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
                  << std::endl;                         // array's indices begin from 0, Output indices begin from 1
        if (!((i + 1) % LINE_TO_PAGE))
        {
            std::cout << std::endl << RESET << YELLOW << "Press Enter for continue." ;
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
        privateChat(user, _user_array[index - 1]);  // array's indices begin from 0, Output indices begin from 1
    }
    catch (std::exception& e)
    {
        std::cout << BOLDRED << e.what() << RESET << std::endl;
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
            auto it = _private_chat_array.begin();
            _private_chat_array.insert(it + findIndexForChat(chat), chat);
            ++_current_chat_number;
        }
        catch (std::exception& e)
        {
            std::cout << BOLDRED << e.what() << RESET << std::endl;
        }
    }
    chat->addMessage(source_user);
}
auto Application::privateChat_editMessage(
    const std::shared_ptr<User>& source_user, const std::shared_ptr<User>& target_user, const std::shared_ptr<Chat>& chat) const -> void
{
    std::cout << std::endl << RESET << YELLOW << "Select message number for editing: " << BOLDGREEN;
    int message_number{Utils::inputIntegerValue()};
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

auto Application::privateChat_deleteMessage(
    const std::shared_ptr<User>& source_user, const std::shared_ptr<User>& target_user, const std::shared_ptr<Chat>& chat) const -> void
{
    std::cout << std::endl << RESET << YELLOW << "Select message number for deleting: " << BOLDGREEN;
    int message_number{Utils::inputIntegerValue()};
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

auto Application::findIndexForChat(const std::shared_ptr<Chat>& chat) const -> int
{
    if (!_current_chat_number) return 0;

    long long first_userID{chat->getFirstUser()->getUserID()};
    long long second_userID{chat->getSecondUser()->getUserID()};

    long long userID{(first_userID << 32) + second_userID};  // Create value for search

    auto start{0};
    auto stop{_current_chat_number - 1};
    auto middle{0};

    auto iteration_number{_current_chat_number};

    auto sgn{0};

    while (iteration_number)
    {
        middle = (start + stop) / 2;

        long long first_userID{_private_chat_array[middle]->getFirstUser()->getUserID()};
        long long second_userID{_private_chat_array[middle]->getSecondUser()->getUserID()};

        long long middleUserID{(first_userID << 32) + second_userID};// Сreate  value for comparison

        sgn = Utils::sign(userID - middleUserID);  // userID < middleUserID -> sng = -1
        switch (sgn)                               // userID == middleUserID -> sng = 0
        {                                          // userID > middleUserID -> sng =  1
            case -1: stop = middle - 1; break;
            case 1: start = middle + 1; break;
            default: break;
        }
        iteration_number /= 2;
    }
// Possible three variants
//    [0][1]    [n]  [n+1]     [n][n+1]   
//   | m            |  m            m  |
//   ^              ^                  ^
//   {   sgn = -1   }               sng =  1
//   m - middle
// ( sgn = -1)  When insertion goes to the beginning of an array or between elements
// ( sgn =  1)  When insertion goes to the end of the array
    if (sgn == 1) return middle + 1; //index correction 
    return middle;
}

auto Application::getPrivateChat(const std::shared_ptr<User>& source_user, const std::shared_ptr<User>& target_user) const
    -> const std::shared_ptr<Chat>&
{
    long long first_userID{source_user->getUserID()};
    long long second_userID{target_user->getUserID()};

    Utils::minToMaxOrder(first_userID, second_userID);

    long long userID{(first_userID << 32) + second_userID};  // Create value for search

    auto start{0};
    auto stop{_current_chat_number - 1};
    auto middle{0};

    auto iteration_number{_current_chat_number};
    auto sgn{0};

    while (iteration_number)
    {
        middle = (start + stop) / 2;

        long long first_userID{_private_chat_array[middle]->getFirstUser()->getUserID()};
        long long second_userID{_private_chat_array[middle]->getSecondUser()->getUserID()};

        long long middleUserID{(first_userID << 32) + second_userID};  // Сreate  value for comparison

        sgn = Utils::sign(userID - middleUserID);  // userID < middleUserID -> sng = -1
                                                   // userID == middleUserID -> sng = 0
        switch (sgn)                               // userID > middleUserID -> sng =  1
        {
            case -1: stop = middle - 1; break;
            case 0:
            {
                return _private_chat_array[middle];
            }
            break;
            case 1: start = middle + 1; break;
            default: break;
        }
        iteration_number /= 2;
    }
    return nullptr;
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
