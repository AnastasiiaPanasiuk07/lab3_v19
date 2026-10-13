#include <iostream>
#include <Windows.h>
#include "Payment.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Payment a;
	a.Display();

	Payment b;
	b.Read();
	b.Display();

	Payment c = b;
	std::cout << "Виведення скопійованого об'єкта c\n";
	c.Display();

	std::string resultText = b.toString();
	std::cout << resultText;

	system("pause");
	return 0;
}