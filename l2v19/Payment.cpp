#include "Payment.h"
#include<iostream>
#include <sstream>

Payment::Payment()
{
    this->lastName = "";
    this->firstName = "";
    this->middleName = "";
    this->salary = 0.0;
    this->taxPercent = 13.0;
    this->startYear = 0;
    this->bonusPercent = 0.0;
    this->workedDays = 0;
    this->totalWorkingDays = 1;
    this->accruedAmount = 0.0;
    this->withheldAmount = 0.0;
}

Payment::Payment(std::string lastName, std::string firstName, std::string middleName, double salary, int startYear, double bonusPercent, int workedDays, int totalWorkingDays, double taxPercent)
{
    this->Init(lastName, firstName, middleName, salary, taxPercent, startYear, bonusPercent, workedDays, totalWorkingDays);
}

Payment::Payment(const Payment& p)
{
    this->lastName = p.lastName;
    this->firstName = p.firstName;
    this->middleName = p.middleName;
    this->salary = p.salary;
    this->bonusPercent = p.bonusPercent;
    this->taxPercent = p.taxPercent;
    this->startYear = p.startYear;
    this->workedDays = p.workedDays;
    this->totalWorkingDays = p.totalWorkingDays;
    this->accruedAmount = p.accruedAmount;
    this->withheldAmount = p.withheldAmount;
}

void Payment::Init(std::string lastName, std::string firstName, std::string middleName, double salary, int startYear, double bonusPercent, int workedDays, int totalWorkingDays, double taxPercent)
{
    this->lastName = lastName;
    this->firstName = firstName;
    this->middleName = middleName;
    this->salary = salary;
    this->startYear = startYear;
    this->bonusPercent = bonusPercent;
    this->workedDays = workedDays;
    this->totalWorkingDays = (totalWorkingDays > 0) ? totalWorkingDays : 1;
    this->taxPercent = 0.0;
    this->accruedAmount = 0.0;
    this->withheldAmount = 0.0;

    this->taxPercent = taxPercent;

    this->CalculateAccrued();
    this->CalculateWithheld();
}
void Payment::Read()
{
    std::cout << " -\n";
    std::cout << "Введіть прізвище: "; std::cin >> this->lastName;
    std::cout << "Введіть ім'я: "; std::cin >> this->firstName;
    std::cout << "Введіть по батькові: "; std::cin >> this->middleName;
    std::cout << "Введіть оклад: "; std::cin >> this->salary;
    std::cout << "Введіть рік вступу на роботу: "; std::cin >> this->startYear;
    std::cout << "Введіть відсоток надбавки: "; std::cin >> this->bonusPercent;
    std::cout << "Введіть кількість відпрацьованих днів: "; std::cin >> this->workedDays;
    std::cout << "Введіть кількість робочих днів у місяці: "; std::cin >> this->totalWorkingDays;
    std::cout << " -\n";

    if (this->totalWorkingDays <= 0)
    {
        this->totalWorkingDays = 1;
    }
    this->taxPercent = 13.0;

    this->CalculateAccrued();
    this->CalculateWithheld();
}
double Payment::CalculateAccrued()
{
    double baseEarned = (this->salary / this->totalWorkingDays) * this->workedDays; double bonusAmount = baseEarned * (this->bonusPercent / 100.0); this->accruedAmount = baseEarned + bonusAmount;
    return this->accruedAmount;
}
double Payment::CalculateWithheld()
{
    this->CalculateAccrued();
    double pension = this->accruedAmount * 0.01;
    double tax = this->accruedAmount * (this->taxPercent / 100.0);
    this->withheldAmount = pension + tax;
    return this->withheldAmount;
}

double Payment::CalculateNetSalary()
{
    return this->CalculateAccrued() - this->CalculateWithheld();
}

int Payment::CalculateExperience(int currentYear) const
{
    if (this->startYear <= 0)
    {
        return 0;
    }
    return (currentYear >= this->startYear) ? (currentYear - this->startYear) : 0;
}

std::string Payment::toString() const
{
    const_cast<Payment*>(this)->CalculateAccrued();
    const_cast<Payment*>(this)->CalculateWithheld();

    std::ostringstream ss;

    std::cout << " -\n";
    std::cout << "Працівник: " << this->lastName << " " << this->firstName << " " << this->middleName << "\n";
    std::cout << "Оклад: " << this->salary << " грн\n";
    std::cout << "Прибутковий податок: " << this->taxPercent << "%\n";
    std::cout << "Рік вступу: " << this->startYear << " \n";
    std::cout << "Стаж:" << this->CalculateExperience(2026) << " років\n";
    std::cout << "Відсоток надбавки: " << this->bonusPercent << "%\n";
    std::cout << "Відпрацьовано днів: " << this->workedDays << " з " << this->totalWorkingDays << "\n";
    std::cout << "Нарахована сума: " << this->accruedAmount << " грн\n";
    std::cout << "Утримана сума: " << this->withheldAmount << " грн\n";
    std::cout << "Сума до виплати: " << (this->accruedAmount - this->withheldAmount) << " грн\n";

    return ss.str();
}
void Payment::Display() const
{
    std::cout << this->toString();
}

Payment::~Payment()
{

}

// Перевантаження операцій 

// Присвоєння
Payment& Payment::operator=(const Payment& p)
{
    if (this != &p)
    {
        this->lastName = p.lastName;
        this->firstName = p.firstName;
        this->middleName = p.middleName;
        this->salary = p.salary;
        this->bonusPercent = p.bonusPercent;
        this->taxPercent = p.taxPercent;
        this->startYear = p.startYear;
        this->workedDays = p.workedDays;
        this->totalWorkingDays = p.totalWorkingDays;
        this->accruedAmount = p.accruedAmount;
        this->withheldAmount = p.withheldAmount;
    }
    return *this;
}

// Інкремент ++a: +1 відпрацьований день
Payment& Payment::operator++()
{
    if (this->workedDays < this->totalWorkingDays)
    {
        this->workedDays++;
    }
    this->CalculateWithheld();
    return *this;
}

// Пост інкремент a++: повертає старе значення
Payment Payment::operator++(int)
{
    Payment old(*this);
    ++(*this);
    return old;
}

// Порівняння за сумою до виплати
bool Payment::operator>(const Payment& p) const
{
    return const_cast<Payment*>(this)->CalculateNetSalary() > const_cast<Payment&>(p).CalculateNetSalary();
}

// Виведення
std::ostream& operator<<(std::ostream& os, const Payment& p)
{
    os << p.toString();
    return os;
}

// Введення
std::istream& operator>>(std::istream& is, Payment& p)
{
    p.Read();
    return is;
}
