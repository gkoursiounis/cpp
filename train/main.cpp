#include <iostream>
#include <cstdlib>
#include <ctime>
#include "train.h"
#include "waggon.h"
#include "linkedList.h"

using namespace std;


int main(int argc, char *argv[])
{
    int N, totalWaggons, maxCapacity, finePrice;

    if(argc==5)
    {
        N = atoi(argv[1]);
        totalWaggons = atoi(argv[2]);
        maxCapacity = atoi(argv[3]);
        finePrice = atoi(argv[4]);
    }
    else
    {
        cout << "Usage: " << argv[0] << " <N> <totalWaggons> <maxCapacity> <finePrice>" << endl;
        return 1;
    }

    srand(time(0));

    train AthensMetro(N, totalWaggons, maxCapacity, finePrice);
    AthensMetro.operate();
    AthensMetro.printStatistics();

    return 0;
}



