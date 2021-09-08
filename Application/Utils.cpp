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
        if (std::cin.fail())  // ���� ���� ������ ��� �����
        {
            std::cin.clear();                                                    // ������� ������ ������ �����
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // ������ ������ �����
            std::cout << "������� �� ���������� ��������!" << std::endl;
            std::cout << "��������� ����: ";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}
