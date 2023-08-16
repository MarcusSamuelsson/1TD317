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

// Funktionen berakna_histogram_abs
void berakna_histogram_abs(string txt, int count[]) 
{
  cout << txt << endl;

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

// Funktionen skriv_histogram_abs
void skriv_histogram_abs(int count[]) 
{
  for(int i = 0; i < ANTAL_BOKSTAVER; i++)
  {
    cout << (char)(i+65) << ": " << count[i] << endl;
  }
}

//--------------------------------------------------------
// Huvudprogram:

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

//--------------------------------------------------------
// Funktionsdefinitioner:


// Redovisning av uppgiften i ord. 
