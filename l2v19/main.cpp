#include <iostream>
#include <Windows.h>
#include "Payment.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Payment a;
	std::cout << a;

	Payment b;
	std::cin >> b;
	std::cout << b;

	Payment c = b;
	std::cout << "Виведення скопійованого об'єкта c\n";
	std::cout << c;

	Payment d;
	d = b;
	std::cout << "Об'єкт d після d = b\n";
	std::cout << d;

	std::cout << "\n ++d (інкремент):\n";
	++d;
	std::cout << d;

	std::cout << "\n d++ (пост інкремент), старе значення:\n";
	std::cout << d++;
	std::cout << "Після d++:\n";
	std::cout << d;

	if (d > b)
		std::cout << "\n d отримує більше, ніж b\n";
	else
		std::cout << "\n d отримує не більше, ніж b\n";
	
	std::string resultText = b.toString();
	std::cout << resultText;

	system("pause");
	return 0;
}