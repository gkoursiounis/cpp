#include <iostream>
#include <cstdlib>
#include <ctime>
#include "waggon.h"
#include "linkedList.h"

using namespace std;

waggon::waggon(int capacity, int fine)
{
    maxCapacity = capacity;
    currentPassengers = 0;
    isChecked = 0;
    offenders = 0;
    avoidedCheck = 0;
    finesCollected = 0;
    finePrice = fine;
    waggonPassengers = new linkedList;
    cout << "A waggon with capacity for " << maxCapacity << " passengers, was created" << endl;
}


waggon::~waggon()
{
    cout << "A waggon was destroyed" << endl;
    delete waggonPassengers;
}


void waggon::inStation(int currentStation, int N)
{

    if(currentStation==1)           //first station (boarding only)
        boarding();
    else if(currentStation==N)      //final station (no boarding)
    {
        offendersDisembarkation();
        disembarkation(currentStation, N);
    }
    else                            //intermediate station (boarding and disembarkation)
    {
        offendersDisembarkation();
        disembarkation(currentStation, N);
        boarding();
    }
    isChecked = rand() % 2;         //1 for ticket check, else 0

    waggonPassengers->print();
    cout << "  Check:" << isChecked << endl;
}


void waggon::betweenStations()
{
    if(isChecked==0)
        return;

    offenders += waggonPassengers->markOffenders();         //traverse the list and find the offenders
}


void waggon::boarding()
{
    int incomingPassengers = rand() % ((maxCapacity-currentPassengers) + 1);
    for(int i=0; i<incomingPassengers; i++)
    {
        waggonPassengers->insertPassenger();
        currentPassengers++;
    }
    cout << "    " << incomingPassengers << " passengers added" << endl;
}


void waggon::disembarkation(const int& currentStation, const int& N)
{
    int localAvoidedCheck = 0;
    int outgoingPassengers ;


    if(currentStation==N)                                       //last station: disembark ALL passengers
        outgoingPassengers = currentPassengers;
    else
        outgoingPassengers = rand() % (currentPassengers + 1);


    for(int i=0; i<outgoingPassengers; i++)
    {
        int randomDelete = (rand() % currentPassengers) + 1;    //passenger with number "randomDelete" disembarks
        if(waggonPassengers->findPassenger(randomDelete)==0)    //if random passenger has no ticket he avoided check
        {
            avoidedCheck++;
            localAvoidedCheck++;
        }
        waggonPassengers->deletePassenger(randomDelete);
        currentPassengers--;
    }
    cout << "    " << outgoingPassengers << " passengers disembarked and " <<
    localAvoidedCheck << " of them avoided check" << endl;
}


void waggon::offendersDisembarkation()
{
    int erases;

    erases = waggonPassengers->deleteOffenders(finesCollected, finePrice, currentPassengers);

    cout << "    " << erases << " offenders disembarked" << endl;
}


void waggon::printStatistics() const
{
    cout << "    Offenders: " << offenders << endl;
    cout << "    Avoided ticket check: " << avoidedCheck << endl;
}
