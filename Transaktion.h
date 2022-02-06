#pragma once
#include <fstream>
#include <string>
using namespace std;

/// <summary>
///  Transaktions Header
/// </summary>

const int MAX_PERSONER = 10;

class Transaktion
{
private:
    string datum_;
    string typ_;
    string namn_;
    double belopp_;
    int    antal_kompisar;
    string *kompisar;

public:
    Transaktion();
    ~Transaktion();
    Transaktion& operator=(const Transaktion& t);
    string hamtaNamn();
    double hamtaBelopp();
    int    hamtaAntalKompisar();
    bool   finnsKompis(const string& namnet);
    bool   lasIn(istream& is);
    void   skrivUt(ostream& os);
    void   skrivTitel(ostream& os);
};
