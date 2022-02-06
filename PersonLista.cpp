#include "PersonLista.h"

#include <iostream>

#include "TransaktionsLista.h"

/// <summary>
///  PersonLista cpp
/// </summary>

PersonLista::PersonLista()
{
	personer = nullptr;
	antal_personer = 0;
}
PersonLista::~PersonLista()
{
	delete[] personer;
}

void PersonLista::laggTill(Person & ny_person)
{
	Person* tempP = new Person[antal_personer+1]; //skapar en person pekare och tilldelar minne antal_personer+1 pers

	for (int i = 0; i < antal_personer; i++) // loopa igenom pers
	{
		tempP[i] = personer[i];
	}
	tempP[antal_personer++] = ny_person; // lägger den nya pers sist i listan och öka antalet
	delete[] personer; // frigör minne
	personer = tempP; // personer pekar nu på den nya listan
}

// använder metoden skrivUt för att skriva ut alla personer
void PersonLista::skrivUtOchFixa(ostream & os)
{
	os << "Antal personer: " << antal_personer << endl;
	for (int i = 0; i < antal_personer; ++i)
	{
		personer[i].skrivUt(os);
	}
}

double PersonLista::summaSkyldig()
{
	return personer->hamtaSkyldig();

}

double PersonLista::summaBetalat()
{
	return personer->hamtaBetalat();
}

double PersonLista::summaPotten()
{
	return personer->hamtaPotten();
}

// kontrollerar om personen finns i listan
bool PersonLista::finnsPerson(const string& namn)
{
	for (int i = 0; i < antal_personer; ++i)
	{
		if (personer[i].hamtaNamn() == namn)
		{
			return true;
		}
	}
	return false;
}