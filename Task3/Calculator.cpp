#include <iostream>
using namespace std;

//***************************************************************************
//Funktion skrivInfo
//Syfte: Skriver ut information om programmets funktion.
void skrivInfo() 
{
    cout << "This program performs simple calculations given two numbers and an operator." << endl << endl
    << "The operators are the following:" << endl << "  a: Addera tal(Example: input 1 and 4 gives 1+2+3+4=10)" << endl 
    << "  m: Multiplicera tal(Example: input 1 and 4 gives 1*2*3*4=24)"
    << endl << "  k: Beräkna kvadratsumman av tal(Example: input 3 and 5 gives 3*3 + 4*4 + 5*5=50)" << endl;
}
//***************************************************************************

//***************************************************************************
//Funktion lasEttTal
//Syfte: Frågar efter ett tal som ska skrivas in av användaren och returnerar det.
//Utparametrar: input - Det tal som användaren anger
int lasEttTal() 
{
    int input = 0;
    
    cout << "Enter a number to be in the calculation: ";
    cin >> input;
    cout << endl;

    return input;
}
//***************************************************************************

//***************************************************************************
//Funktion lasOp
//Syfte: Frågar efter ett operator som ska skrivas in av användaren och returnerar det.
//Utparametrar: input - Den operatorn som användaren anger
char lasOp()
{
    char input;
    cout << "Enter an operator(a, m or k): ";
    cin >> input;
    cout << endl;

    return input;
}
//***************************************************************************

//***************************************************************************
//Funktion ordna
//Syfte: Jämför två tal och sätter dom i storleks ordning (minsta i num1 och största i num2).
//Inparametrar: num1 - första talet som ska jämföras
//              num2 - andra talet som ska jämföras
void ordna(int & num1, int & num2)
{
    if(num2 < num1)
    {
        int temp = num1;
        num1 = num2;
        num2 = temp;
    }
}
//***************************************************************************

//***************************************************************************
//Funktion berakna
//Syfte: Beräknar summan mellan två tal med angiven operator a för addition, m för multiplication och k för kvadrat.
//Inparametrar: num1 - första talet
//              num2 - andra talet
//              op - operatorn
//Utparametrar: result - resultatet av bäräkningen
double berakna(int num1, int num2, char op)
{
    double result = 0;

    // Välj vilken beräkning baserat på operatorn.
    if(op == 'a')
    {
        // Räknar summan mellan num1 och num2
        for(int i = num1; i <= num2; i++) {
            result += (double)i;
        }
    }
    else if(op == 'm')
    {
        result = 1;

        // Räknar talen mellan num1 och num2 multiplicerat med varandra
        for(int i = num1; i <= num2; i++) {
            result *= (double)i;
        }
    }
    else if(op == 'k')
    {
        // Räknar summan av num1 till num2 upphöjt till två
        for(int i = num1; i <= num2; i++) {
            result += (double)(i*i);
        }
    }
    else 
    {
        cout << "Not valid op" << endl;
    }


    return result;
}
//***************************************************************************

//***************************************************************************
//Funktion skrivResultat
//Syfte: Skriver ut inskickat nummer som ett resultat.
void skrivResultat(double res)
{
    cout << "Result: " << res << endl;
}
//***************************************************************************

//***************************************************************************
//Funktion main
//Syfte: Kallar alla funktioner och kör programmet.
int main()
{  
    // Här ska deklaration av variabler finnas
    
    skrivInfo();

    int tal1 = lasEttTal();

    int tal2 = lasEttTal();

    char op = lasOp();

    ordna(tal1, tal2);

    double svar = berakna(tal1, tal2, op);

    skrivResultat(svar);

    return 0;
}
//***************************************************************************