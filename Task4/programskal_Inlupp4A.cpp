//
// Programskal till inl�mningsuppgift 4 - deluppgift A
//
// Hanterar fallet med 26 bokst�ver A-Z

#include <iostream>
#include <ostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;


// Anv�nd g�rna denna globala konstant i programmet
// i st�llet f�r v�rdet 26
const int ANTAL_BOKSTAVER = 26;  //A-Z
// Globala variabler �r ej till�tna

//--------------------------------------------------------
// Funktionsdeklarationer:
// Anv�nd exakt de funktionsnamn som finns nedan

//***************************************************************************
//Funktion berakna_histogram_abs
//Syfte: Beräknar antalet av bokstäver A-Z i given string till array.
//Inparametrar: txt - text som ska räknas på
//              count - array för varje bokstav där antalet anges
void berakna_histogram_abs(string txt, int count[]) 
{
  cout << txt << endl;

  //Gå igenom och räkna på alla A-Z bokstäver och sätt i count[]
  for(int i = 0; i < txt.length(); i++)
  {
    int let = tolower(txt.at(i)) -97;

    //cout << "! " << let << " - " << ((char)tolower(txt.at(i))) << endl;

    if(let >= 0 && let < 26)
    {
      count[let]++;
    }
  }
}
//***************************************************************************

//***************************************************************************
//Funktion skriv_histogram_abs
//Syfte: Skriv ut array av antalet bokstäver i text
//Inparametrar: count - array för varje bokstav där antalet är givet
void skriv_histogram_abs(int count[]) 
{
  //Skriv ut varje bokstav och dess instancer
  for(int i = 0; i < ANTAL_BOKSTAVER; i++)
  {
    cout << (char)(i+65) << ": " << count[i] << endl;
  }
}
//***************************************************************************

//***************************************************************************
//Funktion main
//Syfte: Kallar alla funktioner och kör programmet.
int main()
{
  // Deklarera variabler
  int letterCount[ANTAL_BOKSTAVER] = {0};

  // L�s in en rad med text fr�n tangentbordet
  string input;
    
  cout << "Enter some text: ";
  getline(cin, input);
  cout << endl;

  cout<< "Inpt: " << input << endl;

  // Anropa funktionen berakna_histogram_abs som ber�knar histogrammet
  // och antalet bokst�ver.  
  berakna_histogram_abs(input, letterCount);

  // Anropa funktionen skriv_histogram_abs som skriver ut histogrammet
  skriv_histogram_abs(letterCount);

  return 0;
}
//***************************************************************************

//--------------------------------------------------------
// Funktionsdefinitioner:


// Redovisning av uppgiften i ord. 
// Uppgiften är att skapa ett histogram på en input från användaren
// i en lista där antalet av varje bokstav räknas.
