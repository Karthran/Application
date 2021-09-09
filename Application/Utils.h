#pragma once
#include <string>

#define MAX_INPUT_SIZE 30

class Utils
{
public:
    static bool isOKSelect();
    static int getValue();
    static void printTimeAndData(const tm& timeinfo);
    static void getBoundedString(std::string& string, int size, bool hidden = false);
};
