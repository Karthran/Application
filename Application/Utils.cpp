#include <iostream>

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
