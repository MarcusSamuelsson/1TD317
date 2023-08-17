#include <cstddef>
#include <ostream>
#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string.h>

using namespace std;

const int MAX_PERSONER = 10;
const int MAX_TRANSAKTIONER = 30;

class Transaktion
{
    private:
        string datum;
        string typ;
        string namn;
        double belopp;
        int    antal_kompisar;
        string kompisar[MAX_PERSONER];

    public:
        Transaktion();
        //~Transaktion();
        string hamtaNamn();
        double hamtaBelopp();
        int    hamtaAntalKompisar();
        bool   finnsKompis(const string &namnet);
        bool   lasIn(istream &is);
        void   skrivUt(ostream &os);
        void   skrivTitel(ostream &os);
};

class Person
{
    private:
        string namn;
        double betalat_andras; // ligger ute med totalt
        double skyldig;        // skyldig totalt

    public:
        Person();
        Person(const string &namn, double betalat_andras, double skyldig);
        string hamtaNamn();
        double hamtaBetalat();
        double hamtaSkyldig();
        void   skrivUt(ostream &os);
};

class PersonLista
{
    private:
        int    antal_personer;
        Person personer[MAX_PERSONER];

    public:
        PersonLista();
        //~PersonLista();
        void   laggTill(Person ny_person);
        void   skrivUtOchFixa(ostream &os);
        double summaSkyldig();
        double summaBetalat();
        bool   finnsPerson(const string& namn);
};

class TransaktionsLista
{
    private:
        int         antal_transaktioner;
        Transaktion transaktioner[MAX_TRANSAKTIONER];

    public:
        TransaktionsLista();
        //~TransaktionsLista();
        void   lasIn(istream & is);
        void   skrivUt(ostream & os);
        void   laggTill(Transaktion & t);
        double totalKostnad();
        double liggerUteMed(const string &namnet);
        double arSkyldig(const string &namnet);
        PersonLista FixaPersoner();
}; 

Transaktion:: Transaktion()
: datum(""), typ(""), namn(""), belopp(0), antal_kompisar(0)
{}

string Transaktion:: hamtaNamn() 
{
    return namn;
}

int Transaktion:: hamtaAntalKompisar() 
{
    return antal_kompisar;
}

double Transaktion:: hamtaBelopp() 
{
    return belopp;
}

bool Transaktion:: finnsKompis(const string &namnet) 
{
    for(int i = 0; i < antal_kompisar; i++) 
    {
        if(kompisar[i] == namnet)
         {
            return true;
         }
    }

    return false;
}

void Transaktion:: skrivUt(ostream &os) 
{
    os << datum << " " << typ << " " << namn << " " << belopp << " " << antal_kompisar << " ";

    for(int i = 0; i < antal_kompisar; i++) 
    {
        os << kompisar[i] << " ";
    }
    
    os << endl;
}

void Transaktion:: skrivTitel(ostream &os) 
{
    cout << "(Layout)  Datum   Typ     Namn    Belopp  Antal personer    Namn på kompisar " << endl;
    cout << "(Exempel) 190721  mat     Eva     200     1                 Bosse  Lisa" << endl;
}

bool Transaktion:: lasIn(istream &is) 
{
    is >> datum >> typ >> namn >> belopp >> antal_kompisar;

    for(int i = 0; i < antal_kompisar; i++)
    {
        is >> kompisar[i];
    }

    return !is.eof();
}

Person:: Person()
: namn(""), betalat_andras(0), skyldig(0)
{}

Person:: Person(const string &namn, double betalat_andras, double skyldig)
: namn(namn), betalat_andras(betalat_andras), skyldig(skyldig)
{}

string Person:: hamtaNamn() 
{
    return namn;
}

double Person:: hamtaBetalat() 
{
    return betalat_andras;
}

double Person:: hamtaSkyldig() 
{
    return skyldig;
}

void Person:: skrivUt(ostream &os) 
{
    double payed = hamtaBetalat();
    double debt = hamtaSkyldig();
    double tot = payed - debt;

    if(tot > 0)
    {
        cout << hamtaNamn() << " ligger ute med " << payed << " och är skyldig " << debt << ". Skall ha " << tot << " från potten!" << endl;
    } 
    else if(tot < 0)
    {
        cout << hamtaNamn() << " ligger ute med " << payed << " och är skyldig " << debt << ". Skall betala " << (tot*-1) << " till potten!" << endl;
    }
    else 
    {
        cout << hamtaNamn() << " ligger ute med " << payed << " och är skyldig " << debt << ". Är kvitt!" << endl;
    }
}

PersonLista:: PersonLista()
: antal_personer(0)
{}

void PersonLista:: laggTill(Person ny_person)
{
    for(int i = 0; i < MAX_PERSONER; i++) 
    {
        if(personer[i].hamtaNamn() == "")
        {
            personer[i] = ny_person;
            antal_personer++;
            return;
        }
    } 
}

void PersonLista:: skrivUtOchFixa(ostream &os)
{
    for(int i = 0; i < antal_personer; i++) 
    {
        personer[i].skrivUt(os);
    }
}

double PersonLista:: summaSkyldig()
{
    double totalDebt = 0;

    for(Person person : personer) 
    {
        totalDebt += person.hamtaSkyldig();
    }

    return totalDebt;
}

double PersonLista:: summaBetalat()
{
    double totalPayed = 0;

    for(Person person : personer) 
    {
        totalPayed += person.hamtaBetalat();
    }

    return totalPayed;
}

bool PersonLista:: finnsPerson(const string& namn)
{
    for(Person person : personer) 
    {
        if(person.hamtaNamn() == namn)
        {
            return true;
        }
    }
    
    return false;
}

TransaktionsLista:: TransaktionsLista()
: antal_transaktioner(0)
{}

void TransaktionsLista:: lasIn(istream & is)
{
    // En inläsningsmetod i klassen TransaktionsLista.
    Transaktion t;

    // Så länge det går bra att läsa (filen ej slut)
    while (t.lasIn(is))        
    {
        antal_transaktioner++;
        laggTill( t );
    }
}

void TransaktionsLista:: skrivUt(ostream & os)
{
    for(int i = 0; i < antal_transaktioner; i++)
    {
        transaktioner[i].skrivUt(os);
    }
}

void TransaktionsLista:: laggTill(Transaktion & t)
{
    for(int i = 0; i < MAX_TRANSAKTIONER; i++) 
    {
        if(transaktioner[i].hamtaNamn() == "")
        {
            transaktioner[i] = t;
            return;
        }
    } 
}

double TransaktionsLista:: totalKostnad()
{
    double totalPayed = 0;

    for(Transaktion t : transaktioner)
    {
        totalPayed += t.hamtaBelopp();
    }

    return totalPayed;
}

// En möjlig implementering av liggerUteMed.
double TransaktionsLista:: liggerUteMed(const string &namn)
{
    double summa = 0.;
    for (int i = 0; i < antal_transaktioner; i++)
        if (transaktioner[i].hamtaNamn() == namn)
        summa += transaktioner[i].hamtaBelopp() *
                (1.0 - 1.0 / (double)(transaktioner[i].hamtaAntalKompisar() + 1));
    return summa;
}

double TransaktionsLista:: arSkyldig(const string &namnet)
{
    double skuld = 0;

    for (int i = 0; i < antal_transaktioner; i++) 
    {
        if (transaktioner[i].finnsKompis(namnet))
        {
            skuld += transaktioner[i].hamtaBelopp() / (double)(transaktioner[i].hamtaAntalKompisar() + 1);
        }
    }

    cout << endl;
        
    return skuld;
}

PersonLista TransaktionsLista:: FixaPersoner()
{
    PersonLista pl;

    for(int i = 0; i < antal_transaktioner; i++) 
    {
        string name = transaktioner[i].hamtaNamn();

        if(!pl.finnsPerson(name))
        {
            Person p = Person(name, liggerUteMed(name), arSkyldig(name));
            pl.laggTill(p);
        }
    }

    return pl;
}



//***************************************************************************
//Funktion main
//Syfte: Kallar alla funktioner och kör programmet.
int main()
{
  cout << "Startar med att läsa från en fil." << endl;

  TransaktionsLista transaktioner;
  std::ifstream     is("resa.txt");
  transaktioner.lasIn(is);

  int operation = 1;
  while (operation != 0)
    {
      cout << endl;
      cout << "Välj i menyn nedan:" << endl;
      cout << "0. Avsluta. Alla transaktioner sparas på fil." << endl;
      cout << "1. Skriv ut information om alla transaktioner." << endl;
      cout << "2. Läs in en transaktion från tangentbordet." << endl;
      cout << "3. Beräkna totala kostnaden." << endl;
      cout << "4. Hur mycket ärr en viss person skyldig?" << endl;
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
                cout << "Kan inte hitta personen " << namn << endl;
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
                cout << "Kan inte hitta personen " << namn << endl;
              else
                cout << namn << " ligger ute med " << ligger_ute_med << endl;
              break;
            }
          case 6:
            {
              cout << "Nu skapar vi en personarray och reder ut det hela!" << endl;
              PersonLista lista = transaktioner.FixaPersoner();
              lista.skrivUtOchFixa(cout);
              break;
            }
        }
    }

  std::ofstream os("transaktioner.txt");
  transaktioner.skrivUt(os);

  return 0;
}

//***************************************************************************