#include "TransaktionsLista.h"
#include "PersonLista.h"

/// <summary>
///  TransaktionLista cpp
/// </summary>

// konstruktor
TransaktionsLista::TransaktionsLista()
{
	
	transaktioner = nullptr;
	antal_transaktioner = 0;
}

// destruktor
TransaktionsLista::~TransaktionsLista()
{
	delete[] transaktioner;
}

// läser in värden till ett TransaktionsLista - objekt från / till fil eller tangentbord / skärm. Använder sig av inläsnings - och utskriftsmetoder i klassen Transaktion.
void TransaktionsLista::lasIn(istream & is)
{
	Transaktion t;
	while (t.lasIn(is))
	{
		laggTill(t);
	}
}

// skriver ut information om ett objekt (dvs "aktuella objektet" tillhörande denna klass), dvs attributens värden, antingen till en fil eller till skärmen.
void TransaktionsLista::skrivUt(ostream & os)
{
	os << "Antal transaktioner: " << antal_transaktioner << endl;
	transaktioner->skrivTitel(os);

	for (int i = 0; i < antal_transaktioner; ++i)
	{
		transaktioner[i].skrivUt(os);
	}
}

// lägger till ett nytt transaktionsobjekt sist i arrayen transaktioner.
void TransaktionsLista::laggTill(Transaktion & t)
{
	Transaktion* tempT = new Transaktion[antal_transaktioner + 1]; //skapar en transaktion pekare och tilldelar minne antal_transaktioner+1 Trans

	for (int i = 0; i < antal_transaktioner; i++) // loopa igenom trans
	{
		tempT[i] = transaktioner[i];
	}
	tempT[antal_transaktioner++] = t; // lägger den nya trans sist i listan och öka antalet
	delete[] transaktioner; // frigör minne
	transaktioner = tempT; // transaktioner pekar nu på den nya listan
}

double TransaktionsLista::totalKostnad()
{
	double total = 0;
	for (int i = 0; i < antal_transaktioner; ++i)
	{
		total += transaktioner[i].hamtaBelopp();
	}
	return total;
}
// beräknar hur mycket personen ligger ute med
double TransaktionsLista::liggerUteMed(const string & inskrivnaNamnet)
{
	double summa = 0.;
	for (int i = 0; i < antal_transaktioner; i++)
		if (transaktioner[i].hamtaNamn() == inskrivnaNamnet)
		{
			summa += transaktioner[i].hamtaBelopp() * (1.0 - 1.0 / (transaktioner[i].hamtaAntalKompisar() + 1.0));
		}
	return summa;
}
// beräknar hur mycket personen är skyldig
double TransaktionsLista::arSkyldig(const string & inskrivnaNamnet)
{
	double summa = 0;
	for (int i = 0; i < antal_transaktioner; i++)
		if (transaktioner[i].finnsKompis(inskrivnaNamnet))
		{
			summa += transaktioner[i].hamtaBelopp() / (transaktioner[i].hamtaAntalKompisar() + 1.0);
		}
	return summa;
}

// beräknar hur mycket personen ska ha ifrån potten. (jag gjorde en metod men ett enklare sätt är att subtrahera liggerUteMed och arSkyldig)
double TransaktionsLista::tillPotten(const string & inskrivnaNamnet)
{
	double summa = liggerUteMed(inskrivnaNamnet);
	for (int i = 0; i < antal_transaktioner; i++)
		if (transaktioner[i].finnsKompis(inskrivnaNamnet))
		{
			summa -= transaktioner[i].hamtaBelopp() / (transaktioner[i].hamtaAntalKompisar() + 1.0);
		}
	return summa;
}

// fixar personer i listan och skickar den som ett Personobjekt till en PersonLista.
PersonLista& TransaktionsLista::fixaPersoner()
{
	PersonLista *list = new PersonLista{};

	for (int i = 0; i < antal_transaktioner; ++i)
	{
		string namn = transaktioner[i].hamtaNamn();
		if (!list->finnsPerson(namn))
		{
			Person p(namn, liggerUteMed(namn), arSkyldig(namn), tillPotten(namn));
			list->laggTill(p);
		}
	}
	return *list;
}