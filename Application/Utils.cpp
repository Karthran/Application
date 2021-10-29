#include <iostream>
#include <iomanip>

#include "Utils.h"

auto Utils::isOKSelect() -> bool
{
    char select;
    std::cin >> select;
    if (select != 'Y' && select != 'y') return false;
    return true;
}

auto Utils::inputIntegerValue() -> int
{
    auto value{UNSUCCESSFUL};
    while (true)
    {
        std::cin >> value;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(MAX_INT, '\n');  //, '\n');
            std::cout << "Incorrect value entered!" << std::endl;
            std::cout << "Try again: ";
        }
        else
        {
            std::cin.ignore(MAX_INT, '\n');  //, '\n');
            return value;
        }
    }
}

auto Utils::printTimeAndData(const tm& timeinfo) -> void
{
    std::cout << std::setw(2) << std::setfill('0') << std::right << timeinfo.tm_hour << ":";
    std::cout << std::setw(2) << std::setfill('0') << std::right << timeinfo.tm_min << ":";
    std::cout << std::setw(2) << std::setfill('0') << std::right << timeinfo.tm_sec << "   ";

    std::cout << std::setw(2) << std::setfill('0') << std::right << timeinfo.tm_mday << "/";
    std::cout << std::setw(2) << std::setfill('0') << std::right << timeinfo.tm_mon + 1 << "/";
    std::cout << timeinfo.tm_year + 1900 << std::endl;
}

auto Utils::getString(std::string& string, int size) -> void
{
    std::cin >> string;
}
