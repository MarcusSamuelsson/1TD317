//
// Programskal till inl�mningsuppgift 4 - deluppgift B
//
// Hanterar fallet med 26 bokst�ver A-Z

#include <cstddef>
#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// Globala konstanter:

// Tips: Anv�nd de globala konstanterna ANTAL_BOKSTAVER och ANTAL_SPRAK
// ist�llet f�r v�rdena 26 och 4 i programmet.
const int ANTAL_BOKSTAVER = 26;  //A-Z
const int ANTAL_SPRAK = 4;

// 2d-arrayen TOLK_HJALP inneh�ller bokstavsfrekvensen i %
// f�r fyra spr�k. TOLK_HJALP[0][0] �r frekvensen av
// bokstaven a f�r engelska. TOLK_HJALP[0][25] �r frekvensen av
// bokstaven z f�r engelska.
// Arrayen �r en GLOBAL KONSTANT och skall allts� ej skickas
// som parameter till den funktion som beh�ver den.
const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER]=
       {{8.27,1.48,2.94,4.03,11.78,2.22,1.72,6.77, //engelska
         7.39,0.12,0.81,3.76,2.85,6.71,7.79,1.54,
         0.05,5.95,6.69,9.07,2.66,1.13,2.14,0.19,
         1.89,0.03},
        {7.97,1.40,3.55,3.79,16.89,1.02,1.00,0.75, //franska
         7.08,0.38,0.04,5.51,2.82,8.11,5.19,2.78,
         1.01,6.69,8.35,7.22,6.09,1.35,0.02,0.54,
         0.30,0.15},
        {9.50,1.11,1.53,5.30,8.94,1.74,3.57,3.94,  //svenska
         3.98,0.89,3.26,4.93,3.41,8.46,5.01,1.77,
         0.00,6.73,5.56,9.20,1.94,2.42,0.00,0.05,
         0.45,0.00},
        {5.12,1.95,3.57,5.07,16.87,1.35,3.00,5.79, //tyska
         8.63,0.19,1.14,3.68,3.12,10.64,1.74,0.42,
         0.01,6.30,6.99,5.19,3.92,0.77,1.79,0.01,
         0.69,1.24}};

// Globala variabler �r ej till�tna

//--------------------------------------------------------
// Funktionsdeklarationer:

// Deklarationer av dina egna funktioner
// Anv�nd exakt de funktionsnamn som finns nedan

void berakna_histogram_abs(string txt, int count[]) 
{
  cout << "Input: " << txt << endl << endl;

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

void abs_till_rel(double count[])
{
  double totalLetters = 0;

  for(int i = 0; i < ANTAL_BOKSTAVER; i++) 
  {
    totalLetters += count[i];
  }

  for(int i = 0; i < ANTAL_BOKSTAVER; i++) 
  {
    count[i] = (count[i]/totalLetters)*100;
  }
}

void plotta_histogram_rel(double count[]) 
{
  for(int i = 0; i < ANTAL_BOKSTAVER; i++) 
  {
    double curr = count[i];

    cout << (char)(i+65) << ": ";

    while(curr > 0.25)
    {
      cout << "*";
      curr -= 0.5;
    }

    cout << endl;
  }

  cout << endl;
}

void tolkning(double count[])
{
  string lang[ANTAL_SPRAK] = {"Engelska", "Franska", "Svenska", "Tyska"};
  double kS = 0, topKS = 9999999;
  int topLang = 0;

  for(int i = 0; i < ANTAL_SPRAK; i++) 
  {
    kS = 0;

    for(int j = 0; j < ANTAL_BOKSTAVER; j++)
    {
      kS += (TOLK_HJALP[i][j]-count[j])*(TOLK_HJALP[i][j]-count[j]);
    }

    if(kS < topKS)
    {
      topKS = kS;
      topLang = i;
    }

    cout << lang[i] << ": " << kS << endl;
  }

  cout << "Det mest troliga språket är " << lang[topLang] << " med kvadratsumman " << topKS << endl  << endl;
}

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

string inlasning(string filename)
{
    string input = "", text = "";

    try
    {
      ifstream myReadFile(filename);

      if(myReadFile.fail())
        throw(filename);

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

//--------------------------------------------------------
// Huvudprogram:

int main()
{
  // Deklarera variabler
  int letterCount[ANTAL_BOKSTAVER] = {0};

  // L�s in en rad med text fr�n tangentbordet
  string input;
    
  input = inlasning(namn_pa_fil());

  if(input == "Error")
  {
    return 0;
  }
  
  // Anropa funktionen berakna_histogram_abs som ber�knar histogrammet
  // och antalet bokst�ver.  
  berakna_histogram_abs(input, letterCount);

  double letterCountProc[ANTAL_BOKSTAVER];

  for(int i = 0; i < ANTAL_BOKSTAVER; i++)
  {
    letterCountProc[i] = (double)letterCount[i];
  }

  abs_till_rel(letterCountProc);

  for(int i = 0; i < ANTAL_BOKSTAVER; i++)
  {
    cout << (char)(i+65) << ": " << letterCount[i] << endl;
  }

  cout << endl;

  for(int i = 0; i < ANTAL_BOKSTAVER; i++)
  {
    cout << (char)(i+65) << ": " << letterCountProc[i] << "%" << endl;
  }

  cout << endl;

  plotta_histogram_rel(letterCountProc);

  tolkning(letterCountProc);

  return 0;
}

//--------------------------------------------------------
// Funktionsdefinitioner:




// -------------------------------------------------------
// Rapport om uppgiften
