#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    time_t seconds = time(NULL);
    tm timeinfo;

    localtime_s(&timeinfo , &seconds);
    return 0;
}