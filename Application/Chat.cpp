#include <iostream>
#include <ctime>
#include <iomanip>

#include "Chat.h"
#include "Message.h"
#include "User.h"


Chat::Chat(int max_message_num) : _max_message_num(max_message_num), _current_message_num(0)
{
    _message_array = new Message[_max_message_num];  // TODO Exception
}

Chat::~Chat()
{
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
    if (message_index < 0 || message_index >= _current_message_num) return; // TODO Exception
    Message& message = _message_array[message_index]; 
    
    const tm& timeinfo = message.getMessageCreationTime();

    std::cout << std::setw(120) << std::setfill('-') << "-" << std::endl;

    std::cout << std::setw(5) << std::setfill(' ') << std::right << message_index << ".";
    std::cout << "  Created: ";
    std::cout << std::setw(30) << std::setfill(' ') << std::left << message.getUser()->getUserName();
    std::cout << std::setw(20) << std::setfill(' ');

    std::cout << std::setw(2) << std::setfill('0') << std::right << timeinfo.tm_hour << ":";
    std::cout << std::setw(2) << std::setfill('0') << std::right << timeinfo.tm_min << ":";
    std::cout << std::setw(2) << std::setfill('0') << std::right << timeinfo.tm_sec << "   ";

    std::cout << std::setw(2) << std::setfill('0') << std::right << timeinfo.tm_mday << "/";
    std::cout << std::setw(2) << std::setfill('0') << std::right << timeinfo.tm_mon + 1 << "/";
    std::cout << timeinfo.tm_year + 1900 << std::endl;
    std::cout << std::setw(120) << std::setfill('-') << "-" << std::endl;

    std::cout << message.getMessage() << std::endl;
    std::cout << std::setw(120) << std::setfill('-') << "-" << std::endl;
}

