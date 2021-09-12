#include <iostream>
#include <conio.h>
#include <limits>
#include <iomanip>

#include "Utils.h"

bool Utils::isOKSelect()
{
    char select;
    std::cin >> select;
    if (select != 'Y' && select != 'y') return false;
    return true;
}

int Utils::getValue()
{
    auto value{0};
    while (true)
    {
        std::cin >> value;
        if (std::cin.fail())  // Если были ошибки при вводе
        {
            std::cin.clear();                                                    // очистка флагов ошибок ввода
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // очиска буфера ввода
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

void Utils::printTimeAndData(const tm& timeinfo)
{
    std::cout << std::setw(2) << std::setfill('0') << std::right << timeinfo.tm_hour << ":";
    std::cout << std::setw(2) << std::setfill('0') << std::right << timeinfo.tm_min << ":";
    std::cout << std::setw(2) << std::setfill('0') << std::right << timeinfo.tm_sec << "   ";

    std::cout << std::setw(2) << std::setfill('0') << std::right << timeinfo.tm_mday << "/";
    std::cout << std::setw(2) << std::setfill('0') << std::right << timeinfo.tm_mon + 1 << "/";
    std::cout << timeinfo.tm_year + 1900 << std::endl;
}

void Utils::getBoundedString(std::string& string, int size, bool hidden)
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

void Utils::getString(std::string& string, int size)
{
    char char_string[MAX_INPUT_SIZE];
    std::cin.getline(char_string, size);
    string = char_string;
}

bool Utils::minToMaxOrder(int& min, int& max)
{
    auto isSwap{false};
    if (min > max)
    {
        std::swap(min, max);
        isSwap = true;
    }
    return isSwap;
}
