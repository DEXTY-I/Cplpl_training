#include <iostream>
#include <iomanip>
#include <numbers>

// def вариант - всё разделено на функции, для разбора по строчкам
// вариант для sin(x)

double first_val(double x) // начальное значение a0
{
    return x;
}

double ratio(double x, int i) // шаг нашей прогрессии (множитель)
{
    return -x * x / (2.0 * i * (2 * i + 1));
}

double exact(double x) // вводим идеал значения, с которым будем сравнивать
{
    return std::sin(x);
}

void sum_n(double x, int n, double& sum) // считаем значение n иттераций
{
	double a = first_val(x);
	sum = 0;
	for (int i = 1; i <= n; ++i)
	{
		sum += a;
		a *= ratio(x, i);
	}
}

int sum_eps(double x, double eps, double& sum) // считаем значение с точностью до eps 
{
	const int MAX_ITER = 100000; // защита от бесконечного цикла (от идиота)
	double a = first_val(x);
	sum = 0;
	int i = 1;
	while (std::abs(a) > eps && i <= MAX_ITER)
	{
		sum += a;
		a *= ratio(x, i);
		++i;
	}
	return i - 1;
}

// ---------- Ввод и вывод ----------
int read_int(const std::string& text, int lo, int hi) // проверка корректности ввода для int значений
{
	int v{};
	while (true)
	{
		std::cout << text;
		if (std::cin >> v && v >= lo && v <= hi)
		{
			std::cin.ignore(32000, '\n');
			return v;
		}
		std::cout << "Вы ввели некорректное значение, повторите попытку.\n";
		std::cin.clear();
		std::cin.ignore(32000, '\n');
	}
}

double read_double(const std::string& text) // проверка корректности ввода для double значений
{
	double v{};
	while (true)
	{
		std::cout << text;
		if (std::cin >> v)
		{
			std::cin.ignore(32000, '\n');
			return v;
		}
		std::cout << "Вы ввели некорректное значение, повторите попытку.\n";
		std::cin.clear();
		std::cin.ignore(32000, '\n');
	}
}

void print_result(double x, double sum, int terms)
{
	double ex = exact(x);
	std::cout << std::defaultfloat << std::setprecision(15) << std::left; // сбрасываем «залипший» fixed
	std::cout << std::setw(25) << "Примерное значение:" << sum << '\n';
	std::cout << std::setw(25) << "Точное значение:" << ex << '\n';
	std::cout << std::setw(25) << "Расхождение:" << std::abs(ex - sum) << '\n';
	std::cout << std::setw(25) << "Кол-во членов:" << terms << '\n';
}

bool confirm_exit()
{
	char c{};
	std::cout << "Вы точно хотите выйти? (Y/y - выйти)\n";
	std::cin >> c;
	std::cin.ignore(32000, '\n');
	return c == 'Y' || c == 'y';
}

double x_system()
{
	double x{};
	int unit = read_int("1 - радианы, 2 - градусы: ", 1, 2);
	x = read_double("Введите x: ");
	if (unit == 2) x = x * std::numbers::pi / 180; // приводим к градусам, если это выбрано
	// приводим большой аргумент к промежутку [-pi, pi], иначе ряд теряет точность
	x = std::remainder(x, 2 * std::numbers::pi);
	return x;
}

// ---------- main ----------
int main()
{
	setlocale(LC_ALL, "Russian");
	bool is_end{ false };

	do {
		std::cout << "\n1 - Подсчет последовательности до N.\n";
		std::cout << "2 - Подсчет последовательности до eps.\n";
		std::cout << "3 - Выход из программы.\n";
		int choice = read_int("Выбор: ", 1, 3);

		switch (choice)
		{
		case 1:
		case 2:
		{
			double x = x_system();
			double sum{};
			if (choice == 1)
			{
				int n = read_int("Введите n (1..1000000): ", 1, 1000000);
				sum_n(x, n, sum);
				print_result(x, sum, n);
			}
			else
			{
				double eps = 1E-12;
				for (int j = 0; j < 2; ++j)
				{
					std::cout << "\neps = " << eps << '\n';
					int terms = sum_eps(x, eps, sum);
					print_result(x, sum, terms);
					eps /= 100;
				}
			}
			break;
		}
		case 3:
			is_end = confirm_exit();
			break;
		}
	} while (!is_end);
}