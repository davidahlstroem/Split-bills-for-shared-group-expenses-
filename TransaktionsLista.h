#pragma once
#include <string>
#include "PersonLista.h"
#include "Transaktion.h"

/// <summary>
///  TransaktionLista Header
/// </summary>

const int MAX_TRANSAKTIONER = 30;

class TransaktionsLista
{
private:
    int         antal_transaktioner;
    Transaktion *transaktioner;

public:
    TransaktionsLista(); //konstruktor
    ~TransaktionsLista(); //destruktor
    void   lasIn(istream& is);
    void   skrivUt(ostream& os);
    void   laggTill(Transaktion& t);
    double totalKostnad();
    double liggerUteMed(const string& inskrivnaNamnet);
    double arSkyldig(const string& inskrivnaNamnet);
    double tillPotten(const string& inskrivnaNamnet);
    PersonLista& fixaPersoner();

};
