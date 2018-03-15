#include "classes.h"

int paintings::evaluate(string mov, string con = "good")
{
    int isCondition;
    int isMovement  = (getMovement().compare(mov) == 0)? 1: 0;

    if(con.compare("good") == 0 && getCondition().compare("excellent") == 0)    //exception: the asked for "good",
        isCondition = 1;                                                        //but "excellent" is ok too
    else if(getCondition().compare(con) == 0)
        isCondition = 1;
    else
        isCondition = 0;

    return (isMovement ==1 && isCondition == 1)? 1: 0;
}

int sculptures::evaluate(string mov, string con = "excellent")
{
    int isCondition;
    int isMovement  = (getMovement().compare(mov) == 0)? 1: 0;

    if(getCondition().compare(con) == 0)
        isCondition = 1;
    else
        isCondition = 0;

    return (isMovement ==1 && isCondition == 1)? 1: 0;
}

//END of classes...Auction function

void auction(int N, artifacts **auctionArtifacts, string movement, string condition)
{
    cout << "Auction begins..." << endl << endl;
    for(int i=0; i<N; i++)
    {
        auctionArtifacts[i]->getIndex();
        auctionArtifacts[i]->getInfo();
        cout << endl << "Evaluation: "
             << auctionArtifacts[i]->evaluate(movement, condition) << endl << endl << endl;
    }
    cout << "Auction ends..." << endl << endl;
}
