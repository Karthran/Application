#include <iostream>
#include <ctime>
#include <iomanip>

#include "Chat.h"
#include "Message.h"
#include "User.h"
#include "Utils.h"

Chat::Chat()
{
    std::cout << "Chat constr " << this << std::endl;
}

Chat::~Chat()
{
    std::cout << "Chat destr " << this << std::endl;
}

void Chat::printMessages(int first_index, int number) const
{
    if (first_index < 0 || first_index >= _current_message_num || number <= 0) return;  // TODO Exception

    for (auto i{first_index}; i < number; ++i)
    {
        printMessage(i);
        if (!((i + 1) % MESSAGES_ON_PAGE)) std::cin.get();
    }
}

void Chat::printMessage(int message_index) const
{
    if (message_index < 0 || message_index >= _current_message_num) return;  // TODO Exception

    auto message{_message_array[message_index]};

    const tm& timeinfo{message->getMessageCreationTime()};

    std::cout << std::setw(120) << std::setfill('-') << "-" << std::endl;

    std::cout << std::setw(5) << std::setfill(' ') << std::right << message_index << ".";
    std::cout << "  Created: ";
    std::cout << std::setw(30) << std::setfill(' ') << std::left << message->getUser()->getUserName();
    std::cout << std::setw(20) << std::setfill(' ');

    Utils::printTimeAndData(timeinfo);

    std::cout << std::setw(120) << std::setfill('-') << "-" << std::endl;

    std::cout << message->getMessage() << std::endl;

    if (message->isEdited())
    {
        const tm& edit_timeinfo{message->getMessageEditingTime()};
        std::cout << std::setw(120) << std::setfill('-') << "-" << std::endl;
        std::cout << "Edited: ";
        Utils::printTimeAndData(edit_timeinfo);
    }
    std::cout << std::setw(120) << std::setfill('-') << "-" << std::endl;
}

void Chat::addMessage(std::shared_ptr<User> user)
{
    std::string new_message{};

    std::cout << "Input message: ";
    std::getline(std::cin, new_message);

    std::cout << "Send message?(Y/N):";
    if (!Utils::isOKSelect()) return;

    time_t seconds{time(NULL)};
    tm timeinfo;
    localtime_s(&timeinfo, &seconds);

    _message_array.insertBefore(std::make_shared<Message>(), _current_message_num);

    _message_array[_current_message_num]->setUser(user);
    _message_array[_current_message_num]->setMessage(new_message);
    _message_array[_current_message_num]->setMessageCreationTime(timeinfo);

    ++_current_message_num;
}

void Chat::deleteMessage(std::shared_ptr<User> user, int message_index)
{
    if (message_index < 0 || message_index >= _current_message_num) return;  // TODO Exception

    if (user != _message_array[message_index]->getUser()) return;

    printMessage(message_index);

    std::cout << "Delete message?(Y/N):";
    if (!Utils::isOKSelect()) return;

    _message_array.remove(message_index);

    --_current_message_num;
}

void Chat::editMessage(std::shared_ptr<User> user, int message_index)
{
    if (message_index < 0 || message_index >= _current_message_num) return;  // TODO Exception

    if (user != _message_array[message_index]->getUser()) return;

    printMessage(message_index);

    std::string new_message{};

    std::cout << "Input new message: ";
    std::getline(std::cin, new_message);

    std::cout << "Save changes?(Y/N):";
    if (!Utils::isOKSelect()) return;

    time_t seconds{time(NULL)};
    tm timeinfo;
    localtime_s(&timeinfo, &seconds);

    _message_array[message_index]->editedMessage(new_message, timeinfo);
}