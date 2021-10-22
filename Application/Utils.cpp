#include <iostream>
#include <conio.h>
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
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Incorrect value entered!" << std::endl;
            std::cout << "Try again: ";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

auto Utils::getBoundedString(std::string& string, int size, bool hidden) -> void
{
    auto c{' '};
    auto i{0};
    string.erase();
    while ((c = _getch()) != '\r')
    {
        string.push_back(c);
        if (hidden)
            _putch('*');
        else
            _putch(c);
        if (++i == size)
        {
            while (_getch() != '\r')
            {
            }
            break;
        }
    }
}

auto Utils::getString(std::string& string, int size) -> void
{
    char char_string[MAX_INPUT_SIZE];
    std::cin.getline(char_string, size);
    string = char_string;
}

