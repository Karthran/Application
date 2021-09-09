#include <iostream>
#include <ctime>
#include <iomanip>

#include "Application.h"

#include "Message.h"
#include "User.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "");

    //std::string str;
    //for (auto i{0}; i < 10; ++i)
    //{
    //    std::cin >> str[i];
    //}

    //std::cout << str << std::endl;

    Application app(100);
    app.run();

    time_t seconds = time(NULL);
    tm time_info;

    localtime_s(&time_info, &seconds);

    User user(std::string("UserName"), std::string("UserLogin"), std::string("UserPassword"), 101);

    Message message("Message", &user, time_info);

    const tm& timeinfo = message.getMessageCreationTime();

    int message_index = 123;

    // std::cout << std::setw(120) << std::setfill('-') << "-" << std::endl;
    // std::cout << std::setw(5) << std::setfill(' ') << std::left << message_index << ".";  // TODO
    // std::cout  << "  Created:";
    // std::cout << std::setw(30) << std::setfill(' ') << std::left << message.getUser()->getUserName();
    // std::cout << std::setw(2) << std::setfill('0') << std::right << timeinfo.tm_hour << ":";
    // std::cout << std::setw(2) << std::setfill('0') << std::right << timeinfo.tm_min << ":";
    // std::cout << std::setw(2) << std::setfill('0') << std::right << timeinfo.tm_sec << "   ";

    // std::cout << std::setw(2) << std::setfill('0') << std::right << timeinfo.tm_mday << "/";
    // std::cout << std::setw(2) << std::setfill('0') << std::right << timeinfo.tm_mon + 1 << "/";
    // std::cout << std::setw(4) << std::setfill('0') << std::right << timeinfo.tm_year + 1900 << std::endl;
    // std::cout << std::setw(120) << std::setfill('-') << "-" << std::endl;

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

    //             << timeinfo.tm_sec << std::endl;

    std::cin.get();
    return 0;
}