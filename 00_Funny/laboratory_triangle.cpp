#include <iostream>

int six_seven(double q)
{
    double eps = 10E-5;
    if (abs(q - 67) < eps) { std::cout << "\nААААААА 67 SIX_seVen SiX_sEveX 6767676767\n"; }
    return 0;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    double x1{}, x2{}, x3{}, y1{}, y2{}, y3{};
    double a{}, b{}, c{};

    std::cout << "Введите кординаты x1 y1:\n";
    std::cin >> x1 >> y1;
    std::cout << "Введите кординаты x2 y2:\n";
    std::cin >> x2 >> y2;
    std::cout << "Введите кординаты x3 y3:\n";
    std::cin >> x3 >> y3;

    a = sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));
    b = sqrt(((x1 - x3) * (x1 - x3)) + ((y1 - y3) * (y1 - y3)));
    c = sqrt(((x3 - x2) * (x3 - x2)) + ((y3 - y2) * (y3 - y2)));

    if (a > b) {
        double buffer = a;
        a = b;
        b = buffer;
    }
    if (b > c) {
        double buffer = b;
        b = c;
        c = buffer;
    }
    if (a > b) {
        double buffer = a;
        a = b;
        b = buffer;
    }

    if (a + b > c)
    {
        double eps = 10E-9;
        double cos_c = (a * a + b * b - c * c) / (2 * a * b);

        std::cout << "\n";
        if (abs(cos_c) < eps) {
            std::cout << "Треугольник прямоугольный!\n";
        }
        else if (cos_c >= eps) {
            std::cout << "Треугольник остроугольный!\n";
        }
        else if (cos_c <= -eps) {
            std::cout << "Треугольник тупоугольный!\n";
        }

        if (abs(c - a) < eps)
        {
            std::cout << "Треугольник равносторонний!\n";
        }
        else if (abs(b - a) < eps)
        {
            std::cout << "Треугольник равнобедренный!\n";
        }

        double s = (a * b * sqrt(1 - cos_c * cos_c)) / 2;
        double hight_a{}, hight_b{}, hight_c{};

        hight_a = 2 * s / a;
        hight_b = 2 * s / b;
        hight_c = 2 * s / c;

        std::cout << "\n";
        std::cout << "Высота к стороне a = " << hight_a << std::endl;
        std::cout << "Высота к стороне b = " << hight_b << std::endl;
        std::cout << "Высота к стороне c = " << hight_c << std::endl;

        six_seven(s);
    }
    else { std::cout << "Такого треугольника не существует!" << std::endl; }
}
