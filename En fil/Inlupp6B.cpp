// Inluppg6A.cpp
// David Ahlström
// 2021-08-18
// 

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

//--------------------------------------------------------
// Globala konstanter:
/*const int MAX_PERSONER = 10;
const int MAX_TRANSAKTIONER = 30;*/

//--------------------------------------------------------
// klassdeklarationer
//---------

class Transaktion
{
private:
    string datum_;
    string typ_;
    string namn_;
    double belopp_;
    int    antal_kompisar;
    string* kompisar;

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

class TransaktionsLista
{
private:
    int         antal_transaktioner;
    Transaktion* transaktioner;

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

// Funktionsdeklarationer:

// Huvudprogram:
int main()
{
    setlocale(LC_ALL, "");
    cout << "Startar med att läsa från en fil." << endl;

    TransaktionsLista transaktioner;
    std::ifstream     is("resa.txt");
    transaktioner.lasIn(is);

    int operation = 1;
    while (operation != 0)
    {
        cout << endl;
        cout << "Valj i menyn nedan:" << endl;
        cout << "0. Avsluta. Alla transaktioner sparas på fil." << endl;
        cout << "1. Skriv ut information om alla transaktioner." << endl;
        cout << "2. Läs in en transaktion från tangentbordet." << endl;
        cout << "3. Beräkna totala kostnaden." << endl;
        cout << "4. Hur mycket är en viss person skyldig?" << endl;
        cout << "5. Hur mycket ligger en viss person ute med?" << endl;
        cout << "6. Lista alla personer mm och FIXA" << endl;

        cin >> operation;
        cout << endl;

        switch (operation)
        {
        case 1:
        {
            transaktioner.skrivUt(cout);
            break;
        }
        case 2:
        {
            Transaktion transaktion;
            cout << "Ange transaktion i följande format" << endl;
            transaktion.skrivTitel(cout);
            transaktion.lasIn(cin);
            transaktioner.laggTill(transaktion);
            break;
        }
        case 3:
        {
            cout << "Den totala kostnanden för resan var "
                << transaktioner.totalKostnad() << endl;
            break;
        }
        case 4:
        {
            cout << "Ange personen: ";
            string namn;
            cin >> namn;
            double ar_skyldig = transaktioner.arSkyldig(namn);
            if (ar_skyldig == 0.)
                cout << "Kan inte hitta personen (antagligen for att de inte är skyldiga nåt) " << namn << endl;
            else
                cout << namn << " är skyldig " << ar_skyldig << endl;
            break;
        }
        case 5:
        {
            cout << "Ange personen: ";
            string namn;
            cin >> namn;
            double ligger_ute_med = transaktioner.liggerUteMed(namn);
            if (ligger_ute_med == 0.)
                cout << "Kan inte hitta personen (antagligen for att de inte har lagt ut nåt) " << namn << endl;
            else
                cout << namn << " ligger ute med " << ligger_ute_med << endl;
            break;
        }
        case 6:
        {
            cout << "Nu skapar vi en personarray och reder ut det hela!" << endl;
            PersonLista lista = transaktioner.fixaPersoner();
            lista.skrivUtOchFixa(cout);
            break;
        }
        }
    }

    std::ofstream os("transaktioner.txt");
    transaktioner.skrivUt(os);

    return 0;
}

//klassimplementationer:

//*******************
// Klassen Transaktion
//*******************
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

Transaktion& Transaktion::operator=(const Transaktion& t) // för djupkopiering
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
bool Transaktion::finnsKompis(const string& namnet)
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

bool Transaktion::lasIn(istream& is)
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

void Transaktion::skrivUt(ostream& os)
{
    os << datum_ << "\t" << typ_ << "\t" << hamtaNamn() << "\t" << hamtaBelopp() << "\t" << hamtaAntalKompisar() << "\t";

    for (int i = 0; i < antal_kompisar; ++i)
    {
        os << kompisar[i] << "\t";
    }
    os << endl;
}

void Transaktion::skrivTitel(ostream& os)
{
    os << "Datum" << "\t" << "Typ" << "\t" << "Namn" << "\t" << "Belopp" << "\t" << "Antal och lista  av kompisar" << endl;
}

//*******************
// Klassen Person
//*******************

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

//**************************
// Klassen PersonLista
//**************************

PersonLista::PersonLista()
{
    personer = nullptr;
    antal_personer = 0;
}
PersonLista::~PersonLista()
{
    delete[] personer;
}

void PersonLista::laggTill(Person& ny_person)
{
    Person* tempP = new Person[antal_personer + 1]; //skapar en person pekare och tilldelar minne antal_personer+1 pers

    for (int i = 0; i < antal_personer; i++) // loopa igenom pers
    {
        tempP[i] = personer[i];
    }
    tempP[antal_personer++] = ny_person; // lägger den nya pers sist i listan och öka antalet
    delete[] personer; // frigör minne
    personer = tempP; // personer pekar nu på den nya listan
}

// använder metoden skrivUt för att skriva ut alla personer
void PersonLista::skrivUtOchFixa(ostream& os)
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


//**************************
// Klassen TransaktionsLista
//**************************

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
void TransaktionsLista::lasIn(istream& is)
{
    Transaktion t;
    while (t.lasIn(is))
    {
        laggTill(t);
    }
}

// skriver ut information om ett objekt (dvs "aktuella objektet" tillhörande denna klass), dvs attributens värden, antingen till en fil eller till skärmen.
void TransaktionsLista::skrivUt(ostream& os)
{
    os << "Antal transaktioner: " << antal_transaktioner << endl;
    transaktioner->skrivTitel(os);

    for (int i = 0; i < antal_transaktioner; ++i)
    {
        transaktioner[i].skrivUt(os);
    }
}

// lägger till ett nytt transaktionsobjekt sist i arrayen transaktioner.
void TransaktionsLista::laggTill(Transaktion& t)
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
double TransaktionsLista::liggerUteMed(const string& inskrivnaNamnet)
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
double TransaktionsLista::arSkyldig(const string& inskrivnaNamnet)
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
double TransaktionsLista::tillPotten(const string& inskrivnaNamnet)
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
    PersonLista* list = new PersonLista{};

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

