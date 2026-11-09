#include <iostream>

int main()
{
    int n{};
    std::cin >> n;
    long long x = 1;
    long long y = 0;
    for (int i = 0; i < n; i++)
    {
        std::cout << x << ' ';
        long long z = x;
        x = x + y;
        y = z;
    }
    return 0;
}
// Просто прикольный скрипт, выводит последовательность из n чисел Фибоначчи
