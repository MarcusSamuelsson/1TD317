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

//***************************************************************************
//Funktion Transaktion
//Syfte: Konstruktor för Transaktion.
Transaktion:: Transaktion()
: datum(""), typ(""), namn(""), belopp(0), antal_kompisar(0)
{}
//***************************************************************************

//***************************************************************************
//Funktion hamtaNamn
//Syfte: Hämtar namn från Transaktion.
//Utparametrar: namn - namnet på personen som gjorde transaktionen
string Transaktion:: hamtaNamn() 
{
    return namn;
}
//***************************************************************************

//***************************************************************************
//Funktion hamtaAntalKompisar
//Syfte: Hämtar antalet kompisar på en transaktion.
//Utparametrar: antal_kompisar - Antalet vänner med på transaktionen
int Transaktion:: hamtaAntalKompisar() 
{
    return antal_kompisar;
}
//***************************************************************************

//***************************************************************************
//Funktion hamtaBelopp
//Syfte: Hämtar antalet belopp på en transaktion.
//Utparametrar: belopp - Beloppet på transaktionen
double Transaktion:: hamtaBelopp() 
{
    return belopp;
}
//***************************************************************************

//***************************************************************************
//Funktion finnsKompis
//Syfte: Kollar om en kompis är med i en transaktion baserat på ett namn.
//Inparametrar: namnet - namnet på personen som kollas upp.
//Utparametrar: true - kompisen finns
//            : false - kompisen finns inte
bool Transaktion:: finnsKompis(const string &namnet) 
{
    //Går igenom alla kompisar och letar efter ett namn
    for(int i = 0; i < antal_kompisar; i++) 
    {
        if(kompisar[i] == namnet)
         {
            return true;
         }
    }

    return false;
}
//***************************************************************************

//***************************************************************************
//Funktion skrivUt
//Syfte: Skriver ut infomation om en transaktion.
//Inparametrar: os - output streamen där text ska skrivas ut.
void Transaktion:: skrivUt(ostream &os) 
{
    os << datum << "\t" << typ << "\t" << namn << "\t" << belopp << "\t" << antal_kompisar << "\t\t";

    //Går igenom alla kompisar och skriver ut dom
    for(int i = 0; i < antal_kompisar; i++) 
    {
        os << kompisar[i] << "\t";
    }
    
    os << endl;
}
//***************************************************************************


//***************************************************************************
//Funktion skrivTitel
//Syfte: Skriver ut infomation om hur en transaktion ska skrivas in.
//Inparametrar: os - output streamen där text ska skrivas ut.
void Transaktion:: skrivTitel(ostream &os) 
{
    cout << "(Layout)\tDatum\tTyp\tNamn\tBelopp\tAntal personer\tNamn på kompisar " << endl;
    cout << "(Exempel)\t190721\tmat\tEva\t200\t1\t\tBosse\tLisa" << endl;
}
//***************************************************************************

//***************************************************************************
//Funktion lasIn
//Syfte: Läser in infomation om en transaktion.
//Inparametrar: is - input streamen med informationen.
//Utparametrar: true - input stream är inte klar
//            : false - input stream är vid eof
bool Transaktion:: lasIn(istream &is) 
{
    is >> datum >> typ >> namn >> belopp >> antal_kompisar;

    //Går igenom alla vänner och lägger till dom i kompisar
    for(int i = 0; i < antal_kompisar; i++)
    {
        is >> kompisar[i];
    }

    return !is.eof();
}
//***************************************************************************

//***************************************************************************
//Funktion Person
//Syfte: Konstruktor för Person.
Person:: Person()
: namn(""), betalat_andras(0), skyldig(0)
{}
//***************************************************************************

//***************************************************************************
//Funktion Person
//Syfte: Konstruktor för Person.
//Inparametrar: namn - namnet på personen.
//            : betalat_andras - utlagda pengar av personen
//            : skyldig - det personen är skyldig
Person:: Person(const string &namn, double betalat_andras, double skyldig)
: namn(namn), betalat_andras(betalat_andras), skyldig(skyldig)
{}
//***************************************************************************

//***************************************************************************
//Funktion hamtaNamn
//Syfte: Hämtar namn från Person.
//Utparametrar: namn - namnet på personen
string Person:: hamtaNamn() 
{
    return namn;
}
//***************************************************************************

//***************************************************************************
//Funktion hamtaBetalat
//Syfte: Hämtar vad Person har betalat.
//Utparametrar: betalat_andras - vad personen har betalat
double Person:: hamtaBetalat() 
{
    return betalat_andras;
}
//***************************************************************************

//***************************************************************************
//Funktion hamtaSkyldig
//Syfte: Hämtar vad Person är skyldig.
//Utparametrar: skyldig - vad personen är skyldig
double Person:: hamtaSkyldig() 
{
    return skyldig;
}
//***************************************************************************

//***************************************************************************
//Funktion skrivUt
//Syfte: Skriver ut infomation om en person.
//Inparametrar: os - output streamen där text ska skrivas ut.
void Person:: skrivUt(ostream &os) 
{
    double payed = hamtaBetalat();
    double debt = hamtaSkyldig();
    double tot = payed - debt;

    //Skriver ut text baserat på om ligger till med skulder och betalningar
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
//***************************************************************************

//***************************************************************************
//Funktion PersonLista
//Syfte: Konstruktor för PersonLista.
PersonLista:: PersonLista()
: antal_personer(0)
{}
//***************************************************************************

//***************************************************************************
//Funktion laggTill
//Syfte: Lägg till en ny person i personlistan.
//Inparametrar: ny_person - ny personen som ska läggas till.
void PersonLista:: laggTill(Person ny_person)
{
    //Går igenom listan för att hitta en tom plats att lägga in en ny person
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
//***************************************************************************

//***************************************************************************
//Funktion skrivUtOchFixa
//Syfte: Skriver ut infomation om alla personer.
//Inparametrar: os - output streamen där text ska skrivas ut.
void PersonLista:: skrivUtOchFixa(ostream &os)
{
    //Går igenom och skriver ut info för alla personer
    for(int i = 0; i < antal_personer; i++) 
    {
        personer[i].skrivUt(os);
    }
}
//***************************************************************************


//***************************************************************************
//Funktion summaSkyldig
//Syfte: Räknar ut den totala skulden för alla.
//Utparametrar: totalDebt - den totala skulden.
double PersonLista:: summaSkyldig()
{
    double totalDebt = 0;

    //räkar ihop alla skulder
    for(int i = 0; i < antal_personer; i++) 
    {
        totalDebt += personer[i].hamtaSkyldig();
    }

    return totalDebt;
}
//***************************************************************************

//***************************************************************************
//Funktion summaBetalat
//Syfte: Räknar ut den totala betalningarna för alla.
//Utparametrar: totalPayed - den totala betalningen.
double PersonLista:: summaBetalat()
{
    double totalPayed = 0;

    //räkar ihop alla betalningar
    for(int i = 0; i < antal_personer; i++) 
    {
        totalPayed += personer[i].hamtaBetalat();
    }

    return totalPayed;
}
//***************************************************************************

//***************************************************************************
//Funktion finnsPerson
//Syfte: Kollar om personen finns i personlistan.
//Inparametrar: namn - Namn på personen.
//Utparametrar: true - om personen finns
//            : false - om personen inte finns
bool PersonLista:: finnsPerson(const string& namn)
{
    //Går igenom personer och kollar efter någon som matchan namn
    for(int i = 0; i < antal_personer; i++) 
    {
        if(personer[i].hamtaNamn() == namn)
        {
            return true;
        }
    }
    
    return false;
}
//***************************************************************************

//***************************************************************************
//Funktion TransaktionsLista
//Syfte: Konstruktor för TransaktionsLista.
TransaktionsLista:: TransaktionsLista()
: antal_transaktioner(0)
{}
//***************************************************************************

//***************************************************************************
//Funktion lasIn
//Syfte: Läser in transaktioner till transaktionslistan.
//Inparametrar: is - input streamen med informationen.
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
//***************************************************************************

//***************************************************************************
//Funktion skrivUt
//Syfte: Skriver ut infomation om alla transaktioner.
//Inparametrar: os - output streamen där text ska skrivas ut.
void TransaktionsLista:: skrivUt(ostream & os)
{
    cout << "Datum\tTyp\tNamn\tBelopp\tAntal personer\tNamn på kompisar " << endl;

    //Går igenom och skriver ut alla transaktioner
    for(int i = 0; i < antal_transaktioner; i++)
    {
        transaktioner[i].skrivUt(os);
    }
}
//***************************************************************************

//***************************************************************************
//Funktion laggTill
//Syfte: Lägg till en ny transaktion i transaktionslistan.
//Inparametrar: t - ny transaktion som ska läggas till.
void TransaktionsLista:: laggTill(Transaktion & t)
{
    //Går igenom listan för att hitta en tom plats att lägga in en ny transaktion
    for(int i = 0; i < MAX_TRANSAKTIONER; i++) 
    {
        if(transaktioner[i].hamtaNamn() == "")
        {
            transaktioner[i] = t;
            return;
        }
    } 
}
//***************************************************************************

//***************************************************************************
//Funktion totalKostnad
//Syfte: Räknar ut den totala kostnaden för alla.
//Utparametrar: totalPayed - den totala kostnaden.
double TransaktionsLista:: totalKostnad()
{
    double totalPayed = 0;

    //Kollar igenom alla transaktioner och räknar på totalbelopp
    for(int i = 0; i < antal_transaktioner; i++)
    {
        totalPayed += transaktioner[i].hamtaBelopp();
    }

    return totalPayed;
}
//***************************************************************************

//***************************************************************************
//Funktion liggerUteMed
//Syfte: Räknar ut den vad en person ligger ute med.
//Inparametrar: namn - namn på en person.
//Utparametrar: summa - summa av betelningar för en person.
double TransaktionsLista:: liggerUteMed(const string &namn)
{
    double summa = 0.;

    //Räknar ut total betalning för en person
    for (int i = 0; i < antal_transaktioner; i++)
        if (transaktioner[i].hamtaNamn() == namn)
        summa += transaktioner[i].hamtaBelopp() *
                (1.0 - 1.0 / (double)(transaktioner[i].hamtaAntalKompisar() + 1));
    return summa;
}
//***************************************************************************

//***************************************************************************
//Funktion arSkyldig
//Syfte: Räknar ut den vad en person är skyldig.
//Inparametrar: namn - namn på en person.
//Utparametrar: skuld - summa av skulder för en person.
double TransaktionsLista:: arSkyldig(const string &namnet)
{
    double skuld = 0;

    //Räknar ut total skuld för en person
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
//***************************************************************************

//***************************************************************************
//Funktion FixaPersoner
//Syfte: Går igenom person för person och räknar ut skulder, betalningar och 
//om personer ska lägga till potten eller få från potten.
//Utparametrar: pl - En ny PersonLista.
PersonLista TransaktionsLista:: FixaPersoner()
{
    PersonLista pl;

    //Går igenom alla transaktioner och hittar unika personer
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