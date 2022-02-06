#include "Transaktion.h"

/// <summary>
///  Transaktion cpp
/// </summary>

Transaktion::Transaktion()
{
	belopp_ = 0;
	antal_kompisar = 0;
	kompisar = nullptr;
	
}

Transaktion::~Transaktion()
{
	delete[] kompisar;
}

Transaktion& Transaktion::operator=(const Transaktion & t) // för djupkopiering
{
	if (this != &t)
	{
		delete[] kompisar;
		datum_ = t.datum_;
		typ_ = t.typ_;
		namn_ = t.namn_;
		belopp_ = t.belopp_;
		antal_kompisar = t.antal_kompisar;
		kompisar = new string[antal_kompisar];
		for (int i = 0; i < antal_kompisar; i++)
		{
			kompisar[i] = t.kompisar[i];
		}
	}
	return *this;
}

string Transaktion::hamtaNamn()
{
	return namn_;
}

double Transaktion::hamtaBelopp()
{
	return belopp_;
}

int Transaktion::hamtaAntalKompisar()
{
	return antal_kompisar;
}

// letar igenom arrayen kompisar och returnerar true om namnet finns, annars false.
bool Transaktion::finnsKompis(const string & namnet)
{
	for (int i = 0; i < hamtaAntalKompisar(); ++i)
	{
		if (kompisar[i] == namnet)
		{
			return true;
		}
	}
	return false;
}

bool Transaktion::lasIn(istream & is)
{
	is >> datum_ >> typ_ >> namn_ >> belopp_ >> antal_kompisar;

	
		delete[] kompisar;
		kompisar = new string[antal_kompisar];
	

	for (int i = 0; i < antal_kompisar; ++i) // skriv ut kompislistan
	{
		string n;
		if (is >> n)
		{
			kompisar[i] = n;
		}
	}
	return !is.eof();
	
}

void Transaktion::skrivUt(ostream & os)
{
	os << datum_ << "\t" << typ_ << "\t" << hamtaNamn() << "\t" << hamtaBelopp() << "\t" << hamtaAntalKompisar() << "\t";

	for (int i = 0; i < antal_kompisar; ++i)
	{
		os << kompisar[i] << "\t";
	}
	os << endl;
}

void Transaktion::skrivTitel(ostream & os)
{
	os << "Datum" << "\t" << "Typ" << "\t" << "Namn" << "\t" << "Belopp" << "\t" << "Antal och lista  av kompisar" << endl;
}