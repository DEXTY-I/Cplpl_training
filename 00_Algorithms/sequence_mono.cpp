#include <iostream>
#include <iomanip>
#include <numbers>

// mono вариант - всё в main

int main()
{
	setlocale(LC_ALL, "Russian"); 

	// переменные
	bool is_end{ false }; // выход из программы
	int choice{}; // выбор в UI
	int x_system{}; // система счисления x
	int n{}; // кол-во итераций
	char confrim_exit{}; // подтверждение выхода
	double x{}; // x
	double s{ 0 }; // сумма

	// константы
	const double PI = std::numbers::pi;
	const int MAX_ITER = 100000;
	const double eps = 1E-12;

	// основной алгоритм
	do {
	// Вывод UI
	std::cout << "\n1 - Подсчет последовательности до N.\n";
	std::cout << "2 - Подсчет последовательности до eps.\n";
	std::cout << "3 - Выход из программы.\n";
	// Ввод и проверка значения choice (выбор пользователя)
	std::cout << "Ввод: ";
	std::cin >> choice;
	while (std::cin.fail() || choice > 3 || choice < 1)
	{
		std::cout << "\nВы ввели некорректное значение, попробуйте ещё раз.\n";
		std::cin.clear();
		std::cin.ignore(32000, '\n');
		std::cout << "Ввод: ";
		std::cin >> choice;
	}
	std::cin.ignore(32000, '\n');
	// заранее вводим x (для избежания повторения кода)
	if (choice == 1 || choice == 2)
	{
		// для тригонаметрических функций
		std::cout << "\nВыберите систему счисления.\n";
		std::cout << "1 - радианы, 2 - градусы: ";
		std::cin >> x_system;
		while (std::cin.fail() || x_system > 2 || x_system < 1)
		{
			std::cout << "\nВы ввели некорректное значение, попробуйте ещё раз.\n";
			std::cin.clear();
			std::cin.ignore(32000, '\n');
			std::cout << "Выберите систему счисления.\n";
			std::cout << "1 - радианы, 2 - градусы: ";
			std::cin >> x_system;
		}
		std::cin.ignore(32000, '\n');
		// вводим x
		std::cout << "Введите x : ";
		std::cin >> x;
		while (std::cin.fail())
		{
			std::cout << "\nВы ввели некорректное значение, попробуйте ещё раз.\n";
			std::cin.clear();
			std::cin.ignore(32000, '\n');
			std::cout << "Введите x : ";
			std::cin >> x;
		}
		std::cin.ignore(32000, '\n');
		// преобразуем x в нужную систему
		if (x_system == 2) 
		{
			x = x * PI / 180;
		}
		x = std::fmod(x, PI * 2);
	}

	// переменные от x 
	double a0 = x; // первый член ряда
	double exact = sin(x); // эталонное значение
	
	switch (choice)
	{
	case 1: // N итераций
	{
		std::cout << "Введите N : ";
		std::cin >> n;
		while (std::cin.fail())
		{
			std::cout << "\nВы ввели некорректное значение, попробуйте ещё раз.\n";
			std::cin.clear();
			std::cin.ignore(32000, '\n');
			std::cout << "Введите N : ";
			std::cin >> n;
		}
		std::cin.ignore(32000, '\n');

		double a = a0;
		for (int i{1}; i <= n; ++i)
		{
			s += a;
			a *= (-1 * x * x) / (2.0 * i * (2 * i + 1));
		}
		break;
	}
	case 2: // с точностью до eps
	{
		int i = 1;
		double a = a0;
		while (abs(a) > eps && i < MAX_ITER)
		{
			s += a;
			a *= (-1 * x * x) / (2.0 * i * (2 * i + 1));
			++i;
		}
		n = --i;
		std::cout << "\neps = " << eps << '\n';
		break;
	}
	case 3: // выход
	{
		std::cout << "Вы точно хотите выйти? (Y/y - выйти)\n";
		std::cin >> confrim_exit;
		if (confrim_exit == 'Y' || confrim_exit == 'y') { is_end = true; }
		else { std::cin.ignore(32000, '\n'); }
		break;
	}

	}
	// вывод значений
	if (choice == 1 || choice == 2) 
	{
		std::cout << std::fixed << std::setprecision(20) << std::left;
		std::cout << std::setw(25) << "Примерное значение:" << s << '\n';
		std::cout << std::setw(25) << "Точное значение:" << exact << '\n';
		std::cout << std::setw(25) << "Расхождение:" << std::abs(exact - s) << '\n';
		std::cout << std::setw(25) << "Кол-во членов:" << n << '\n';
	}
	
	} while (!is_end);
}
