#include <iostream>

// Nubmer 1 

int main()
{
	setlocale(LC_ALL, "Russian");

	double x{}, y{};
	int choice{};

	std::cout << "Введите координаты х и у:\n";
	std::cin >> x >> y;
	std::cout << "\n";

	/* Выпишем все функции и зоны:
	Функции:
	y = x^2 - 5
	y = 2 - 2*(x^2)
	y = x + 1
	Зоны:
	A, B, C, D, E, F, G, H, K, L, M, N, P, Q, R
	Выделенная зона:
	(D + E + F + L)
	Зоны для проверки:
	(R + G), B, M, C
	*/

	std::cout << "Если хотите проверить выделенную зону, нажмите 1\n";
	std::cout << "Если хотите проверить зону (R + G), нажмите 2\n";
	std::cout << "Если хотите проверить зону B, нажмите 3\n";
	std::cout << "Если хотите проверить зону M, нажмите 4\n";
	std::cout << "Если хотите проверить зону C, нажмите 5\n";
	std::cin >> choice;
	std::cout << "\n";

	switch (choice) // Создадим 5 кейсов для каждого варианта ввода + default если будет введено некорректное значение
	{
	case 1: 
		if ((y <= 2 - 2 * (x * x) && y >= x + 1) || (y >= x * x - 5 && y <= x + 1 && y >= 0) || (y >= 2 - 2 * (x * x) && y >= x * x - 5 && y <= x + 1 && x <= 0)) // (попали в D) || (попали в (E + F)) || (попали в L)
			{std::cout << "Вы попали в выделенную зону!\n";}
		else 
			{std::cout << "ВЫ ЛУЗЕР!!!\n";}
		break; 
	case 2:
		if (y <= x * x - 5 && y >= 2 - 2 * (x * x) && y <= x + 1 && x >= 0)
			{std::cout << "Вы попали в зону (R + G)!\n";}
		else
			{std::cout << "ВЫ ЛУЗЕР!!!\n";}
		break;
	case 3:
		if (y >= x * x - 5 && y >= 2 - 2 * (x * x) && y >= x + 1 && y >= 0)
			{std::cout << "Вы попали в зону B!\n";}
		else
			{std::cout << "ВЫ ЛУЗЕР!!!\n";}
		break;
	case 4:
		if (y >= x * x - 5 && y <= 2 - 2 * (x * x) && y <= 0)
			{std::cout << "Вы попали в зону M!\n";}
		else
			{std::cout << "ВЫ ЛУЗЕР!!!\n";}		
		break;
	case 5:
		if (y <= x * x - 5 && y >= x + 1 && x >= 0)
			{std::cout << "Вы попали в зону C!\n";}
		else
			{std::cout << "ВЫ ЛУЗЕР!!!\n";}
		break;
	default: 
		std::cout << "Некорректное действие!\n";	
	}

}