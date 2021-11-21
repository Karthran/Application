#include <iostream>
#include <iomanip>

#if defined(_WIN32)
#include <conio.h>
#elif defined(__linux__)
#include <unistd.h>
#include <limits.h>
#endif

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
            std::cin.ignore(IGNORED_NUM, '\n');
            std::cout << "Incorrect value entered!" << std::endl;
            std::cout << "Try again: ";
        }
        else
        {
            std::cin.ignore(IGNORED_NUM, '\n');
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

//auto Utils::getBoundedString(std::string& string, int size, bool hidden) -> void
//{
//    auto c{' '};
//    auto i{0};
//    string.erase();
//    while ((c = _getch()) != '\r')
//    {
//        string.push_back(c);
//        if (hidden)
//            _putch('*');
//        else
//            _putch(c);
//        if (++i == size)
//        {
//            while (_getch() != '\r')
//            {
//            }
//            break;
//        }
//    }
//}

auto Utils::getString(std::string& string, size_t size) -> void
{
    std::cin >> string;
    std::cin.ignore(IGNORED_NUM, '\n');
    if (size && size < string.size()) string.resize(size);
}

auto Utils::getPassword(std::string& password, const std::string& text) -> void
{
#if defined(_WIN32)

    std::cout << std::endl << text;
    std::cout << BOLDGREEN;

    auto c{' '};
    auto i{0};
    password.erase();
    while ((c = _getch()) != '\r')
    {
        password.push_back(c);
        _putch('*');
        if (++i == MAX_INPUT_SIZE)
        {
            while (_getch() != '\r')
            {
            }
            break;
        }
    }
#elif defined(__linux__)
    password = std::string(getpass(text.c_str()));
#endif
    std::cout << RESET << std::endl;
}

auto Utils::getSelfPath(std::string& path) -> void 
{
#if defined(_WIN32)
    path.erase();
#elif defined(__linux__)
    char buff[PATH_MAX];
    ssize_t len = ::readlink("/proc/self/exe", buff, sizeof(buff) - 1);
    if (len != -1)
    {
        for (auto i{len - 1}; i >= 0; --i)
        {
            if (buff[i] != '/') continue;
            buff[i + 1] = '\0';
            path = std::string(buff);
            break;
        }
    }
#endif
}
