#pragma once
#include <iostream>
#include <string>
#include <sstream>
class Payment
{
private:
	std::string lastName; //Прізвище
	std::string firstName; //ім'я
	std::string middleName; //По батькові

	double salary = 0.0;        // Оклад
	double bonusPercent = 0.0;  // Відсоток надбавки
	double taxPercent = 13.0;   // Прибутковий податок (13%)

	int startYear = 0;          //Рік вступу на робту
	int workedDays = 0;         // Відпрацьовано днів
	int totalWorkingDays = 0;   // Всього робочих днів у місяці

	double accruedAmount = 0.0; // Нарахована сума
	double withheldAmount = 0.0;// Утримана сума

public:
	Payment(); // Конструктор за замовчуванням
	Payment(std::string lastName, std::string firstName, std::string middleName, double salary, int startYear, double bonusPercent, int workedDays, int totalWorkingDays, double taxPercent = 13.0);
	Payment(const Payment& p);   // Конструктор копіювання 
	~Payment(); // Деструктор

	void Init(std::string lastName, std::string firstName, std::string middleName, double salary, int startYear, double bonusPercent, int workedDays, int totalWorkingDays, double taxPercent = 13.0);
	void Read();
	void Display() const;
	std::string toString() const;

	double CalculateAccrued();                      // Обчислення нарахованої суми
	double CalculateWithheld();                     // Обчислення утриманої суми
	double CalculateNetSalary();                    // Обчислення отриманої суми
	int CalculateExperience(int currentYear) const; // Обчислення стажу

	// Перевантаження оперецій
	Payment& operator=(const Payment& p);           // присвоєння
	Payment& operator++();                          // інкремент ++a
	Payment operator++(int);                        // пост інкремент a++
	bool operator>(const Payment& p) const;         // порівняння за сумою до виплати
	friend std::ostream& operator<<(std::ostream& os, const Payment& p);
	friend std::istream& operator>>(std::istream& is, Payment& p);

};

