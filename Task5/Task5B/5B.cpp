//
// Programskal till Inlupp5A
//
// Hanterar fallet med 26 bokst�ver A-Z

#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// Globala konstanter:

// Tips: Anv�nd de globala konstanterna ANTAL_BOKSTAVER och ANTAL_SPRAK
// ist�llet f�r v�rdena 26 och 4 i programmet.
const int ANTAL_BOKSTAVER = 26;  // A-Z
const int ANTAL_SPRAK = 4;

// 2d-arrayen TOLK_HJALP inneh�ller bokstavsfrekvensen i %
// f�r fyra spr�k. TOLK_HJALP[0][0] �r frekvensen av
// bokstaven a f�r engelska. TOLK_HJALP[0][25] �r frekvensen av
// bokstaven z f�r engelska.
// Arrayen �r en GLOBAL KONSTANT och skall allts� ej skickas
// som parameter till den funktion som beh�ver den.
const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER]=
       {{8.27,1.48,2.94,4.03,11.78,2.22,1.72,6.77, // engelska
         7.39,0.12,0.81,3.76,2.85,6.71,7.79,1.54,
         0.05,5.95,6.69,9.07,2.66,1.13,2.14,0.19,
         1.89,0.03},
        {7.97,1.40,3.55,3.79,16.89,1.02,1.00,0.75, // franska
         7.08,0.38,0.04,5.51,2.82,8.11,5.19,2.78,
         1.01,6.69,8.35,7.22,6.09,1.35,0.02,0.54,
         0.30,0.15},
        {9.50,1.11,1.53,5.30,8.94,1.74,3.57,3.94,  // svenska
         3.98,0.89,3.26,4.93,3.41,8.46,5.01,1.77,
         0.00,6.73,5.56,9.20,1.94,2.42,0.00,0.05,
         0.45,0.00},
        {5.12,1.95,3.57,5.07,16.87,1.35,3.00,5.79, // tyska
         8.63,0.19,1.14,3.68,3.12,10.64,1.74,0.42,
         0.01,6.30,6.99,5.19,3.92,0.77,1.79,0.01,
         0.69,1.24}};

// Globala variabler �r ej till�tna

//--------------------------------------------------------
// H�r kommer klassdeklarationen
class Text {
  private:
    string text;
    int histogram[ANTAL_BOKSTAVER] = {0};
    double histogramRel[ANTAL_BOKSTAVER] = {0};
    int totalLetters = 0;

  public:
  //***************************************************************************
  //Funktion setText
  //Syfte: Sätter text till inskickad text.
  //Inparametrar: nyText - texten som ska räknas på
  void setText(const string &nyText) 
  {
    text = nyText;
  }
  //***************************************************************************

  //***************************************************************************
  //Funktion beraknaHistogram
  //Syfte: Kallar på funktionerna som räknar ut histogramets abs och relativa
  void beraknaHistogram() {
    if(beraknaHistogramAbs())
    {
      abs_till_rel();
    }
  }
  //***************************************************************************

  //***************************************************************************
  //Funktion beraknaHistogramAbs
  //Syfte: Beräknar antalet av bokstäver A-Z i given string till array.
  bool beraknaHistogramAbs()
  {
    //Gå igenom och räkna på alla A-Z bokstäver och sätt i histogram och räkna totala antalet
    for(int i = 0; i < text.length(); i++)
    {
      int let = tolower(text.at(i)) -97;

      //cout << "! " << let << " - " << ((char)tolower(txt.at(i))) << endl;

      if(let >= 0 && let < 26)
      {
        totalLetters++;
        histogram[let]++;
      }
    }

    if(totalLetters > 0)
    {
      return true;
    }

    return false;
  }
  //***************************************************************************

  //***************************************************************************
  //Funktion skriv_histogram_abs
  //Syfte: Skriv ut array av antalet bokstäver i text
  void skrivHistogramAbs() 
  {
    //Skriv ut histogram
    for(int i = 0; i < ANTAL_BOKSTAVER; i++)
    {
      cout << (char)(i+65) << ": " << histogram[i] << endl;
    }

    cout << endl;

    //Skriv ut histogramRel
    for(int i = 0; i < ANTAL_BOKSTAVER; i++)
    {
      cout << (char)(i+65) << ": " << histogramRel[i] << "%" << endl;
    }

    cout << endl;
  }
  //***************************************************************************

  //***************************************************************************
//Funktion abs_till_rel
//Syfte: Beräkna antalet bokstäver procentuellt.
void abs_till_rel()
{
  //Använd totalen för att få det procentuella numeret
  for(int i = 0; i < ANTAL_BOKSTAVER; i++) 
  {
    histogramRel[i] = ((double)histogram[i]/totalLetters)*100;
  }
}
//***************************************************************************

//***************************************************************************
//Funktion plotta_histogram_rel
//Syfte: Skriv ut en lista där den procentuella arrayen representeras av "*" per 0.5%
//Inparametrar: count - array för att se det procentuella värdet på varje bokstav  
void plotta_histogram_rel() 
{
  //Gå igenom varje bokstav i count
  for(int i = 0; i < ANTAL_BOKSTAVER; i++) 
  {
    double curr = histogramRel[i];

    cout << (char)(i+65) << " ";

    //Skriv ut "*" och subthera med 0.5 för att få en för varje 0.5% med avrundning
    while(curr >= 0.25)
    {
      cout << "*";
      curr -= 0.5;
    }

    cout << endl;
  }

  cout << endl;
}
//***************************************************************************

//***************************************************************************
//Funktion tolka
//Syfte: Använder sig av den beräknade arrayen i procent och TOLK_HJALP för att lista ut vilket språk texten är i.  
string tolka()
{
  string lang[ANTAL_SPRAK] = {"Engelska", "Franska", "Svenska", "Tyska"};
  double kS = 0, topKS = 9999999;
  int topLang = 0;

  //Gå igenom varje språk i TOLK_HJALP för att se vilket som matchar
  for(int i = 0; i < ANTAL_SPRAK; i++) 
  {
    kS = 0;

    //Använd formel för att räkna vilket språk count mest efterliknar (mindre är bättre)
    for(int j = 0; j < ANTAL_BOKSTAVER; j++)
    {
      kS += (TOLK_HJALP[i][j]-histogramRel[j])*(TOLK_HJALP[i][j]-histogramRel[j]);
    }

    if(kS < topKS)
    {
      topKS = kS;
      topLang = i;
    }

    cout << lang[i] << ": " << kS << endl;
  }

  return lang[topLang];
}
//***************************************************************************
};

// -------------------------------------------------------

//***************************************************************************
//Funktion namn_pa_fil
//Syfte: Tar in ett namn på filen som ska läsas och ser till att det avslutas med ".txt".
//Utparametrar: input - Den filen som ska läsas
string namn_pa_fil()
{
  string input = "";

  cout << "Enter a the name of a text file: ";
  cin >> input;

  if(!(input.rfind(".txt") == (input.length()-4)))
  {
    input.append(".txt");
  }

  cout << "File: " << input << endl;

  return input;
}
//***************************************************************************

//***************************************************************************
//Funktion inlasning
//Syfte: Läser in filen angiven i namn_pa_fil och kollar ifall den existerar.
//Inparametrar: filename - Den filen som ska läsas
//Utparametrar: text - Texten läst av filen eller "Error" om filen ej finns
string inlasning(string filename)
{
    string input = "", text = "";

    try
    {
      ifstream myReadFile(filename);

      if(myReadFile.fail())
        throw(filename);

      //Läser in text i filen och lägg in i text variabeln tills filen är klar.
      while (getline (myReadFile, input)) {
        // Output the text from the file
        //cout << input << endl;
        text.append(input);
      }

      //cout << text << endl;

      myReadFile.close();
    }
    catch(string file)
    {
      cout << "File " << file << " could not be found!" << endl;
      return "Error";
    }
    

    return text;
}
//***************************************************************************

// Huvudprogram:

//***************************************************************************
//Funktion main
//Syfte: Kallar alla funktioner och kör programmet.
int main()
{
 // Deklarera variabler
  string text;
  Text minText;  // Ett objekt av typen Text skapas
    
  text = inlasning(namn_pa_fil());

  if(text == "Error")
  {
    return 0;
  }

  // Skicka str�ngen text till objektet minText
  minText.setText( text );

  // Ber�kna och skriv ut histogrammet
  minText.beraknaHistogram();
  minText.skrivHistogramAbs();
  minText.plotta_histogram_rel();
  string lang = minText.tolka();
  cout << "Det mest troliga språket är " << lang << endl;

  return 0;
}
//***************************************************************************

// -------------------------------------------------------
// H�r skriver du klassimplementationen


//--------------------------------------------------------
// Funktionsdefinitioner:




// -------------------------------------------------------
// Rapport om uppgiften
