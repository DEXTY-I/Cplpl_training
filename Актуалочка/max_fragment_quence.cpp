#include <iostream>

int main()
{
    setlocale(LC_ALL, "Russian");

    int total{ 1 }, cnt{ 1 };
    double current{}, prev{};
    int is_up{ 0 };   //  1 - возрастающая, -1 - убывающая, 0 - не определена
    int is_up_m{ 0 }; //  Направление для самой длинной последовательности

    if (std::cin >> prev) // вводим первое значие и сразу проверияем
    {
        while (std::cin >> current) // цикл ввода второго значения
        {
            if (current > prev) 
            {
                if (is_up == 1) { // если направление верно, добавляем к временному счётчику
                    cnt++;
                }
                else if (is_up == -1 || is_up == 0) {
                    // Если направление изменилось, сохраняем старый результат
                    if (cnt > total) {
                        total = cnt;
                        is_up_m = is_up;
                    }
                    cnt = 2; // Текущая пара (prev и current) образуют начало новой цепочки
                    is_up = 1;
                }
            }
            else if (current < prev)
            {
                if (is_up == -1) {
                    cnt++;
                }
                else if (is_up == 1 || is_up == 0) {
                    if (cnt > total) {
                        total = cnt;
                        is_up_m = is_up;
                    }
                    cnt = 2;
                    is_up = -1;
                }
            }
            else // current == prev
            {
                if (cnt > total) {
                    total = cnt;
                    is_up_m = is_up;
                }
                cnt = 1;
                is_up = 0; // Последовательность прервалась
            }
            prev = current;
        }

        // Проверка последнего участка после выхода из цикла
        if (cnt > total) {
            total = cnt;
            is_up_m = is_up;
        }

        // Вывод результатов
        if (total > 1 && is_up_m != 0) {
            std::cout << "Максимальная длина последовательности = " << total << std::endl;
            std::cout << "Максимальная последовательность ";
            if (is_up_m == 1) std::cout << "возрастающая\n";
            else std::cout << "убывающая\n";
        }
        else {
            std::cout << "Нет никакой монотонной последовательности\n";
        }
    }
}
