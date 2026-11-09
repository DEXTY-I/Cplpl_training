#include <iostream>

int main()
{
    setlocale(LC_ALL, "Russian");

    int cnt{}, total{ 1 };
    double x{};
    double first_max{}, second_max{};

    if (std::cin >> first_max) // вводим первое значие и сразу проверияем
    {
        second_max = first_max;
        while (std::cin >> x) // цикл ввода второго значения
        {
            if (x > first_max)
            {
                second_max = first_max;
                first_max = x;
                cnt++;
                total = 1;
            }
            else if (x > second_max)
            {
                second_max = x;
                cnt++;
                total = 1;
            }
            else if (x == second_max) total++;
        }
        std::cout << second_max << " | " << cnt << " | " << total << std::endl;
    }
}
