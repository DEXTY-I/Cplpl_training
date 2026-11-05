#include <iostream>
#include <iomanip>
#include <numbers>

// def вариант (сложный) - всё разделено на функции, для разбора по строчкам
// тут вариант сразу с несколькими функциями, мб ещё действий позже добавлю

const int SERIES_COUNT = 3; // константа - количество поддерживаемых функций

std::string series_name(int s) // список доступных функций (тут ввели тип данных string - строка)
{
	switch (s)
	{
	case 1: return "sin(x)";
	case 2: return "cos(x)";
	case 3: return "exp(x)";
	}
	return "";
}
// * везде кейсы именно в таком порядке 1 - sin, 2 - cos, 3 - exp

double first_val(int s, double x) // начальное значение функции, a0 (с чего начинается ряд Маклорена)
{
	switch (s)
	{
	case 1: return x;
	case 2: return 1;
	case 3: return 1;
	}
	
}
// * ряд Маклорена - частный случай ряда Тейлора, где x_0 = 0

double ratio(int s, double x, int i) // шаг нашей прогрессии (множитель)
{
	switch (s)
	{
	case 1: return -x * x / (2.0 * i * (2 * i + 1)); // sin
	case 2: return (-x * x) / ((2 * i + 1) * (2 * i + 2)); // cos
	case 3: return x / (i + 1); // exp
	} 
	// на всякий случай дублирую где какая функция
}

double exact(int s, double x) // находим эталон, с которым будем сравнивать
{
	switch (s)
	{
		case 1: return std::sin(x);
		case 2: return std::cos(x);
		case 3: return std::exp(x);
	}
}

void sum_n(int s, double x, int n, double& sum) // считаем значение n иттераций
{
	double a = first_val(s, x); // берём a0 из функции first_val 
	sum = 0;
	for (int i = 1; i <= n; ++i) // стандартный цикл суммы n раз
	{
		sum += a;
		a *= ratio(s, x, i); // умнажаем на соответсвующий множитель из ratio
	}
}

int sum_eps(int s, double x, double eps, double& sum) // считаем значение с точностью до eps 
{
	const int MAX_ITER = 100000; // защита от бесконечного цикла (от идиота)
	double a = first_val(s, x); // берём a0 из функции first_val 
	sum = 0;
	int i = 1;
	while (std::abs(a) > eps && i <= MAX_ITER) // стандартный цикл суммы с ограничением иттераций по предельному значению (или количеству в крайнем случае)
	{
		sum += a;
		a *= ratio(s, x, i);
		++i;
	}
	return i - 1;
}

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

void print_result(int s, double x, double sum, int terms) // удобный вывод всех результатов
{
	double ex = exact(s, x); // берем эталонное значение из exact
	std::cout << std::defaultfloat << std::setprecision(15) << std::left; // сбрасываем «залипший» fixed
	std::cout << std::setw(25) << "Примерное значение:" << sum << '\n';
	std::cout << std::setw(25) << "Точное значение:" << ex << '\n';
	std::cout << std::setw(25) << "Расхождение:" << std::abs(ex - sum) << '\n';
	std::cout << std::setw(25) << "Кол-во членов:" << terms << '\n';
}

bool confirm_exit() // подтверждение выхода из программы
{
	char c{};
	std::cout << "Вы точно хотите выйти? (Y/y - выйти)\n";
	std::cin >> c;
	std::cin.ignore(32000, '\n');
	return c == 'Y' || c == 'y';
}

double x_system(int s) // приведение значений x для sin и cos
{
	double x{};
	if (s == 1 || s == 2) // если выбрали sin или cos, уточняем какую систему использовать
	{
		int unit = read_int("1 - радианы, 2 - градусы: ", 1, 2);
		x = read_double("Введите x: ");
		if (unit == 2) x = x * std::numbers::pi / 180; // если выбрали градусы переводим радианы в градусы
		x = std::remainder(x, 2 * std::numbers::pi); // приводим большой аргумент к промежутку [-pi, pi], иначе ряд теряет точность
	}
	else
	{
		x = read_double("Введите x: "); // иначе просто спрашиваем значение, никуда не переводим
	}
	return x; // возвращаем итоговый x
}

// ---------- main ----------
int main()
{
	setlocale(LC_ALL, "Russian"); // русский язык (это кто-то забыл....?)
	bool is_end{ false }; // флаг, что алгоритм не завершен

	do {
		std::cout << "\n1 - Подсчет последовательности до N.\n";
		std::cout << "2 - Подсчет последовательности до eps.\n";
		std::cout << "3 - Выход из программы.\n";
		int choice = read_int("Выбор: ", 1, 3); // проверка на идиота через функцию

		switch (choice)
		{
		case 1: // хз, оказалось удобнее сделать всё в 1 кейсе, иллюзия выбора)))
		case 2:
		{
			std::cout << "Выберите ряд:\n";
			for (int s = 1; s <= SERIES_COUNT; ++s)
				std::cout << s << " - " << series_name(s) << '\n';
			int s = read_int("Ряд: ", 1, SERIES_COUNT); // выбор ряда, от 1 до констаты их количества

			double x = x_system(s); // вводим x 
			double sum{};
			if (choice == 1) // если считаем n итераций
			{
				int n = read_int("Введите n (1..1000000): ", 1, 1000000);
				sum_n(s, x, n, sum);
				print_result(s, x, sum, n);
			}
			else // иначе считаем до eps
			{
				double eps = 1E-12;
				for (int j = 0; j < 2; ++j)
				{
					std::cout << "\neps = " << eps << '\n';
					int terms = sum_eps(s, x, eps, sum);
					print_result(s, x, sum, terms);
					eps /= 100; // второй круг, для меньшего eps (не помню зачем, но это было)
				}
			}
			break;
		}
		case 3: // кейс выхода из цикла
			is_end = confirm_exit(); // уточняем, точно-ли пользователь хочет выйти
			break;
		}
	} while (!is_end); // проверка условия цикла...
}