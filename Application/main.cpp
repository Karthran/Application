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

void insertionSort(int* arr, int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;

        // Сдвигаем элементы arr[0..i-1], которые больше чем key, на одну позицию вперед
        // ваш код
        for (; j >= 0; --j)
        {
            if (key < arr[j])
                arr[j + 1] = arr[j];
            else
                break;
        }
        arr[j + 1] = key;
    }
}
// void swap(int* a, int* b)  // функция для смены местами двух значений
//{
//    int temp = *a;
//    *a = *b;
//    *b = temp;
//}

void selectionSort(int arr[15], int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        int first = arr[i];
        int j = i + 1;
        for (; j < n; ++j)
        {
            if (first > arr[j])
            {
                std::swap(arr[i], arr[j]);
                break;
            }
        }
    }
    // ваш код
}

int main()
{
    setlocale(LC_ALL, "");

    int b = 5;
    int c = 10;

    int a = Utils::sign(b - c);
    switch (a)
    {
        case -1: std::cout << "-1" << std ::endl;
            break;
        case 1: std::cout << "-1" << std ::endl; break;
        default: break;
    }

    int arr[]{
        23,
        26,
        17,
        5,
        33,
        25,
        26,
        32,
        39,
        11,
        2,
        17,
        30,
        -1,
        3,
    };

    selectionSort(arr, 15);

    // int size = 20;
    // std::cout << BOLDRED << UNDER_LINE << "bold red text" << RESET;
    // std::cin >> size;

    Application app;
    app.run();

    return 0;
}