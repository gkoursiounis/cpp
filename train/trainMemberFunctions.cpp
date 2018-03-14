#include <iostream>
#include "train.h"
#include "waggon.h"

using namespace std;

train::train(int n, int waggons, int capacity,int fine)
{
    N = n;
    totalWaggons = waggons;
    trainWaggons = new waggon*[totalWaggons];

    for(int i=0; i<totalWaggons; i++)
        trainWaggons[i] = new waggon(capacity, fine);   //array of pointers to waggons that contain lists of passengers

    cout << "A metro train with " << totalWaggons << " waggons, was created" << endl;
}


train::~train()
{
    cout << "A metro train was destroyed" << endl;

    for(int i=0; i<totalWaggons; i++)
        delete trainWaggons[i];
    delete trainWaggons;
}


void train::operate()
{
    for(int i=1; i<N; i++)
    {
        cout << "In Station: " << i << endl;
        for(int j=0; j<totalWaggons; j++)
        {
            trainWaggons[j]->inStation(i, N);
            cout << endl;
        }
        for(int j=0; j<totalWaggons; j++)
            trainWaggons[j]->betweenStations();
    }

    cout << "In Station: " << N << " (Last station)" << endl;  //final station (no boarding)

    for(int j=0; j<totalWaggons; j++)
    {
        trainWaggons[j]->inStation(N, N);
        cout << endl;
    }
}


void train::printStatistics() const
{
    cout << "Statistics";

    int totalFines=0;
    for(int i=0; i<totalWaggons; i++)
    {
        totalFines += trainWaggons[i]->getFinesCollected();
        cout << endl;
        trainWaggons[i]->printStatistics();
    }
    cout << "Total fine amount is: " << totalFines << " euros" << endl << endl;
}
