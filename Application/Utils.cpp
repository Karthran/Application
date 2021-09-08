#include <iostream>
#include <iomanip>

#include "Utils.h"

bool Utils::isOK()
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
            std::cout << "Введено не правильное значение!" << std::endl;
            std::cout << "Повторите ввод: ";
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

const std::string& Utils::getBoundedString(int size) 
{
    std::string string{};
    for (auto i{0}; i < size; ++i)
    {
        std::cin >> string[i];
    }

    std::cin.clear();                                                    // очистка флагов ошибок ввода
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // очиска буфера ввода

    return string;
}
