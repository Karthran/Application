#include <iostream>
#include <ctime>
#include <iomanip>

#include "Application.h"

#include "Message.h"
#include "User.h"
#include "Utils.h"

#include "Array.h"
class TestClass
{
public:
    TestClass() { std::cout << "Constructor" << std::endl; }
    ~TestClass() { std::cout << "Destructor" << std::endl; }
    void print() const { std::cout << "TestClass" << this << std::endl; }
};


int main()
{
    setlocale(LC_ALL, "");

    //int size = 20;
    //std::cout << BOLDRED << UNDER_LINE << "bold red text" << RESET;
    //std::cin >> size;


    Application app;
    app.run();

    return 0;

}