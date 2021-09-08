#include <iostream>
#include <ctime>
#include <iomanip>

#include "Chat.h"
#include "Message.h"
#include "User.h"
#include "Utils.h"

Chat::Chat(int max_message_num) : _max_message_num(max_message_num), _current_message_num(0)
{
    _message_array = new Message*[_max_message_num];  // TODO Exception
}

Chat::~Chat()
{
///////////////////////////////////////////////////////////////////////////////////
    for (auto i{0}; i < _current_message_num; ++i)
    {
        delete _message_array[i];
    }
///////////////////////////////////////////////////////////////////////////////////
    delete[] _message_array;
}

void Chat::printMessages(int first_index, int number) const
{
    if (first_index < 0 || first_index >= _current_message_num) return;  // TODO Exception
    for (auto i{first_index}; i < number; ++i)
    {
        printMessage(i);
    }
}

void Chat::printMessage(int message_index) const
{
    if (message_index < 0 || message_index >= _current_message_num) return;  // TODO Exception
    Message* message = _message_array[message_index];

    const tm& timeinfo = message->getMessageCreationTime();

    std::cout << std::setw(120) << std::setfill('-') << "-" << std::endl;

    std::cout << std::setw(5) << std::setfill(' ') << std::right << message_index << ".";
    std::cout << "  Created: ";
    std::cout << std::setw(30) << std::setfill(' ') << std::left << message->getUser()->getUserName();
    std::cout << std::setw(20) << std::setfill(' ');

    Utils::printTimeAndData(timeinfo);

    //std::cout << std::setw(2) << std::setfill('0') << std::right << timeinfo.tm_hour << ":";
    //std::cout << std::setw(2) << std::setfill('0') << std::right << timeinfo.tm_min << ":";
    //std::cout << std::setw(2) << std::setfill('0') << std::right << timeinfo.tm_sec << "   ";
    //std::cout << std::setw(2) << std::setfill('0') << std::right << timeinfo.tm_mday << "/";
    //std::cout << std::setw(2) << std::setfill('0') << std::right << timeinfo.tm_mon + 1 << "/";
    //std::cout << timeinfo.tm_year + 1900 << std::endl;

    std::cout << std::setw(120) << std::setfill('-') << "-" << std::endl;

    std::cout << message->getMessage() << std::endl;

    if (message->isEdited())
    {
        const tm& edit_timeinfo = message->getMessageEditingTime();

            Utils::printTimeAndData(edit_timeinfo);

        //std::cout << std::setw(120) << std::setfill('-') << "-" << std::endl;
        //std::cout << "  Edited: ";
        //std::cout << std::setw(2) << std::setfill('0') << std::right << edit_timeinfo.tm_hour << ":";
        //std::cout << std::setw(2) << std::setfill('0') << std::right << edit_timeinfo.tm_min << ":";
        //std::cout << std::setw(2) << std::setfill('0') << std::right << edit_timeinfo.tm_sec << "   ";
        //std::cout << std::setw(2) << std::setfill('0') << std::right << edit_timeinfo.tm_mday << "/";
        //std::cout << std::setw(2) << std::setfill('0') << std::right << edit_timeinfo.tm_mon + 1 << "/";
        //std::cout << timeinfo.tm_year + 1900 << std::endl;
    }
    std::cout << std::setw(120) << std::setfill('-') << "-" << std::endl;
}

void Chat::addMessage(const User& user)
{
    if (_current_message_num >= _max_message_num) return;  // TODO

    std::string new_message{};

    std::cout << "Input message: ";
    std::cin >> new_message;

    std::cout << "Send message?(Y/N):";
    if (!Utils::isOK()) return;

    time_t seconds{time(NULL)};
    tm timeinfo;
    localtime_s(&timeinfo, &seconds);

     _message_array[_current_message_num] = new Message();

    _message_array[_current_message_num]->setUser(&user);
    _message_array[_current_message_num]->setMessage(new_message);
    _message_array[_current_message_num]->setMessageCreationTime(timeinfo);

    ++_current_message_num;
}

void Chat::deleteMessage(int message_index)
{
    if (message_index < 0 || message_index >= _current_message_num) return;  // TODO Exception

    printMessage(message_index);

    std::cout << "Delete message?(Y/N):";
    if (!Utils::isOK()) return;

///////////////////////////////////////////////////////////////////////////////////
    delete _message_array[message_index];
///////////////////////////////////////////////////////////////////////////////////

    for (auto i{message_index}; i < _current_message_num - 1; ++i)
    {
        _message_array[i] = _message_array[i + 1];
    }
    --_current_message_num;
}

void Chat::editMessage(int message_index) 
{
    if (message_index < 0 || message_index >= _current_message_num) return;  // TODO Exception

    printMessage(message_index);

    std::string new_message{};

    std::cout << "Input new message: ";
    std::cin >> new_message;

    std::cout << "Save changes?(Y/N):";
    if (!Utils::isOK()) return;

    time_t seconds{time(NULL)};
    tm timeinfo;
    localtime_s(&timeinfo, &seconds);

    _message_array[message_index]->editedMessage(new_message, timeinfo);
}