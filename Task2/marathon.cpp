#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>
using namespace std;

//***************************************************************************
//Funktion main
//Syfte: Beräknar och skriver ut den snabbaste tiden av tävlande i ett lopp.
int main()
{
    int startNumber = 1;
    int startHour, startMin, startSec;
    int endHour, endMin, endSec;
    int timeHour, timeMin, timeSec;

    int bestStartNumber = -1;
    int bestTimeHour, bestTimeMin, bestTimeSec;

    int totalParticipants;

    // Ta all input, räkna på tid och ta ut det bästa.
    // Loopar till användaren har satt in all sin infomation och väljer att avsluta.
    while(true) 
    {
        cout << "Startnummer? ";
        cin >> startNumber;

        if(startNumber <= 0) 
        {
            break;
        }

        cout << "Starttid? ";
        cin >> startHour >> startMin >> startSec;
        cout << "Måltid? ";
        cin >> endHour >> endMin >> endSec;

        totalParticipants++;
        
        timeHour = 0; timeMin = 0; timeSec = 0;

        // Räkna på hur lång tid det tog för nuvarande tävlande
        if(endSec < startSec) 
        {
            timeSec = 60 - startSec + endSec;
            timeMin = 59;
        } 
        else 
        {
            timeSec = endSec - startSec;
        }

        if(endMin < startMin) 
        {
            timeMin = (timeMin + 60 - startMin + endMin)%60;
            timeHour = 23;
        } 
        else if(endMin == startMin && timeMin != 0) 
        {
            timeHour = 23;
        } 
        else 
        {
            timeMin = (timeMin + endMin - startMin)%60;
        }

        if(endHour < startHour) 
        {
            timeHour = (timeHour + 24 - startHour + endHour)%24;
        } 
        else 
        {
            timeHour = (timeHour + endHour - startHour)%24;
        }

        // Sätt bästa tid till nuvarande om ingen är satt än
        if(bestStartNumber == -1) 
        {
            bestStartNumber = startNumber;
            bestTimeSec = timeSec;
            bestTimeMin = timeMin;
            bestTimeHour = timeHour;
            continue;
        }

        // Jämför och se om den nya tiden är bättre än den nuvarande bästa
        if(bestTimeHour < timeHour) 
        {
            continue;
        } 
        else if(bestTimeHour > timeHour) 
        {
            bestStartNumber = startNumber;
            bestTimeSec = timeSec;
            bestTimeMin = timeMin;
            bestTimeHour = timeHour;
        } 
        else 
        {
            if(bestTimeMin < timeMin) 
            {
                continue;
            } 
            else if(bestTimeMin > timeMin) 
            {
                bestStartNumber = startNumber;
                bestTimeSec = timeSec;
                bestTimeMin = timeMin;
                bestTimeHour = timeHour;
            } 
            else 
            {
                if(bestTimeSec < timeSec) 
                {
                    continue;
                } 
                else if(bestTimeSec > timeSec) 
                {
                    bestStartNumber = startNumber;
                    bestTimeSec = timeSec;
                    bestTimeMin = timeMin;
                    bestTimeHour = timeHour;
                }
            }
        }
    } //slut på while (startNumber <= 0)

    // Kolla om det finns några tävlande
    if(totalParticipants > 0) 
    {
        cout << "Vinnare är startnr: " << bestStartNumber << endl;
        cout << "Tim: " << bestTimeHour << " Min: " << bestTimeMin << " Sek: " << bestTimeSec << endl;
        cout << "Antal tävlande: " << totalParticipants << endl;
    }
    else 
    {
        cout << "Inga tävlande" << endl;
    }
        
    cout << "Programmet avslutas" << endl;

    return 0;
}
//***************************************************************************