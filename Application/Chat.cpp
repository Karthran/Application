#include <iostream>
#include <ctime>
#include <iomanip>

#include "Chat.h"
#include "Message.h"
#include "User.h"
#include "Utils.h"

Chat::Chat()
{
    /*std::cout << "Chat constr " << this << std::endl;*/
}

Chat::~Chat()
{
   /* std::cout << "Chat destr " << this << std::endl;*/
}

auto Chat::printMessages(int first_index, int number) const -> void
{

    for (auto i{first_index}; i < number; ++i)
    {
        printMessage(i);
        if (!((i + 1) % MESSAGES_ON_PAGE)) std::cin.get(); // Suspend via MESSAGES_ON_PAGE messages
    }
}

auto Chat::printMessage(int message_index) const -> void
{

    auto message{_message_array[message_index]};

    const tm& timeinfo{message->getMessageCreationTime()};

    std::cout << BOLDCYAN << std::setw(120) << std::setfill('-') << "-" <<  std::endl;
    std::cout << BOLDGREEN << std::setw(5) << std::setfill(' ') << std::right << message_index + 1 << "."
                                            << RESET;  // array's indices begin from 0, Output indices begin from 1
    std::cout << YELLOW << "  Created: ";
    std::cout << BOLDYELLOW << std::setw(MAX_INPUT_SIZE) << std::setfill(' ') << std::left << message->getUser()->getUserName();
    std::cout << std::setw(20) << std::setfill(' ') << RESET << YELLOW;

    Utils::printTimeAndData(timeinfo);

    std::cout <<  CYAN << std::setw(120) << std::setfill('-') << "-" <<  std::endl;
    std::cout << BOLDYELLOW << message->getMessage() << RESET << std::endl;

    if (message->isEdited())
    {
        const tm& edit_timeinfo{message->getMessageEditingTime()};
        std::cout << CYAN << std::setw(120) << std::setfill('-') << "-" << std::endl;
        std::cout << YELLOW  << "Edited: ";
        Utils::printTimeAndData(edit_timeinfo);
    }
    std::cout << BOLDCYAN << std::setw(120) << std::setfill('-') << "-" << RESET << std::endl;
}

auto Chat::addMessage(const std::shared_ptr<User>& user) -> void
{
    std::string new_message{};

    std::cout << std::endl << YELLOW << "Input message: " << BOLDGREEN;
    std::getline(std::cin, new_message);
    std::cout << RESET;
    std::cout << BOLDYELLOW << "Send message?(Y/N):" << BOLDGREEN;
    if (!Utils::isOKSelect()) return;
    std::cout << RESET;

    time_t seconds{time(NULL)};
    tm timeinfo;
    localtime_s(&timeinfo, &seconds);

    auto it = _message_array.end();

    _message_array.insert(it, std::make_shared<Message>(new_message,user,timeinfo));

    ++_current_message_num;
}

auto Chat::deleteMessage(const std::shared_ptr<User>& user, int message_index) -> void
{

    if (user != _message_array[message_index]->getUser()) return;

    printMessage(message_index);

    std::cout << BOLDYELLOW << "Delete message?(Y/N):" << BOLDGREEN;
    if (!Utils::isOKSelect()) return;
    std::cout << RESET;

    auto it = _message_array.begin();
    _message_array.erase(it + message_index);

    --_current_message_num;
}

auto Chat::editMessage(const std::shared_ptr<User>& user, int message_index) -> void
{

    if (user != _message_array[message_index]->getUser()) return;

    printMessage(message_index);

    std::string new_message{};

    std::cout << YELLOW << "Input new message: " << BOLDGREEN;
    std::getline(std::cin, new_message);
    std::cout << RESET;

    std::cout << BOLDYELLOW << "Save changes?(Y/N):" << BOLDGREEN;
    if (!Utils::isOKSelect()) return;
    std::cout << RESET;

    time_t seconds{time(NULL)};
    tm timeinfo;
    localtime_s(&timeinfo, &seconds);

    _message_array[message_index]->editedMessage(new_message, timeinfo);
}