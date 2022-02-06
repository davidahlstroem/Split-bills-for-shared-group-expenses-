#include "Person.h"
#include <iostream>


/// <summary>
///  Person cpp
/// </summary>

Person::Person()
{
	betalat_andras_ = 0;
	skyldig_ = 0;
	ska_ha_fran_potten = 0;
}

//konstruktor
Person::Person(const std::string& namn, double betalat_andras, double skyldig, double till_potten)
{
	namn_ = namn;
	betalat_andras_ = betalat_andras;
	skyldig_ = skyldig;
	ska_ha_fran_potten = till_potten;
}

string Person::hamtaNamn()
{
	return namn_;
}

double Person::hamtaBetalat()
{
	return betalat_andras_;
}

double Person::hamtaSkyldig()
{
	return skyldig_;
}
double Person::hamtaPotten()
{
	return ska_ha_fran_potten;
}
void Person::skrivUt(ostream& os)
{
	os << hamtaNamn() << " ligger ute med " << hamtaBetalat() << " och ar skyldig " << hamtaSkyldig();

	double summa = hamtaPotten();
	if (summa <= 0)
	{
		summa = fabs(summa);
		os << ". Skall lägga " << summa << " till potten!" << endl;
	}
	else os << ". Skall ha " << hamtaPotten() << " från potten!" << endl;
}
