#pragma once
#include <string>
#include "Person.h"
#include "Transaktion.h"
using namespace std;

/// <summary>
///  PersonLista Header
/// </summary>
/// 
class PersonLista
{
private:
    int    antal_personer;
    Person *personer;

public:
    PersonLista();
    ~PersonLista();
    void   laggTill(Person& ny_person);
    void   skrivUtOchFixa(ostream& os);
    double summaSkyldig();
    double summaBetalat();
    double summaPotten();
    bool   finnsPerson(const string& namn);
};


