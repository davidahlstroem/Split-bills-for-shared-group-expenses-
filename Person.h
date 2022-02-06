#pragma once
#include <string>
using namespace std;

/// <summary>
///  Person cpp
/// </summary>

class Person
{
private:
    std::string namn_;
    double betalat_andras_; // ligger ute med totalt
    double skyldig_;       // skyldig totalt
    double ska_ha_fran_potten; // ska ha från potten totalt

public:
    Person();
    Person(const string& namn, double betalat_andras, double skyldig, double till_potten);
    string hamtaNamn();
    double hamtaBetalat();
    double hamtaSkyldig();
    double hamtaPotten();
    void   skrivUt(ostream& os);
};
