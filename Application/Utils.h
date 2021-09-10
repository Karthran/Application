#pragma once
#include <string>

#define MAX_INPUT_SIZE 30
#define UNSUCCESSFUL -1
#define MAX_MESSAGES_IN_CHAT 10000
#define MESSAGES_ON_PAGE 5
#define LINE_TO_PAGE 15

class Utils
{
public:
    static bool isOKSelect();
    static int getValue();
    static void printTimeAndData(const tm& timeinfo);
    static void getBoundedString(std::string& string, int size, bool hidden = false);
    static bool minToMaxOrder(int& min, int& max);
};
