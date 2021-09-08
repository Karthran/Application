#pragma once
#include <string>

#define MAX_INPUT_SIZE 30

class Utils
{
public:
    static bool isOK();
    static int getValue();
    static void printTimeAndData(const tm& timeinfo);
    static const std::string& getBoundedString(int size);
};
