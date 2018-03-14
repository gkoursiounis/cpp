#include <iostream>
#include <cstdlib>
#include <ctime>
#include "linkedList.h"

using namespace std;

//member functions for class passenger

passenger::passenger()
{
    hasTicket = rand() % 2;
    hasDiscount = rand() % 2;
    iwasCaught = 0;
    myNumber = 0;
}


//member functions for class linkedList

linkedList::linkedList()
{
    head=NULL;
}


linkedList::~linkedList()           //code taken from oop lab :)
{
    node *temp = head;
    while( temp != NULL)
    {
        node *deleteNode = temp;
        temp = temp->link;
        delete deleteNode;
    }
}


void linkedList::insertPassenger()  //insert AT START like a real train waggon
{
    node *tempList;
    tempList = head;
    head = new node;
    head->link = tempList;
}


void linkedList::deletePassenger(int n)        //delete n-nth node
{
    node **traverse=&head, *tempList;
    const int isFirstElement = n;

    while (*traverse != NULL)
        if (n--==1)
        {
            tempList = *traverse;
            *traverse = (*traverse)->link;
            delete tempList;
            if(n==0 && isFirstElement==1)       //1-st node exception
            {
                head = *traverse;
                break;
            }
        }
        else
            traverse = &((*traverse)->link);
}


int linkedList::findPassenger(int n)
{
    node *traverse = head;      //help list node
    while (traverse != NULL)
        if (n--==1)
            return traverse->Passenger.getTicket();
        else
            traverse = traverse->link;
    return 0;
}


void linkedList::print() const
{
    node *temp = head;          //help list node
    int counter = 0;
    while(temp != NULL)
    {
        temp = temp->link;
        counter++;
    }
    cout << "    Total passengers: " << counter;
}


int linkedList::markOffenders()
{
    int counter = 1, offenders = 0;
    node *traversingList;                               //help list node

    traversingList = head;

    while(traversingList != NULL)
    {
        traversingList->Passenger.setNumber(counter);   //give passenger a unique number(passenger.myNumber)
        if(traversingList->Passenger.getTicket()==0)    //check if passenger has ticket
        {
            offenders++;
            traversingList->Passenger.setCatch();      //passenger has no ticket so we mark him
        }
        counter++;
        traversingList = traversingList->link;
    }
    return offenders;
}


int linkedList::deleteOffenders(int& finesCollected, const int finePrice, int &currentPassengers)
{
    node *traversingList;                                                   //help list node
    int erases = 0;

    traversingList = head;

    while(traversingList != NULL)
    {
        if(traversingList->Passenger.getChatch()==1)                        //passenger caught during check
        {
            int discount = traversingList->Passenger.getDiscount();         //if discount = 1 he pays the half fine
            if(discount==1)                                                 //fine offenders...
                finesCollected += finePrice/2;
            else
                finesCollected += finePrice;


            int counter = traversingList->Passenger.getNumber();            //...and disembark them
            deletePassenger(counter-erases);                                //traversing list in ascending order. For every
            erases++;                                                       //erase, element's position is decreased by 1.
            currentPassengers--;                                            //Final element position = first position - erases
        }                                                                   //first position is indicated by "counter"
        traversingList = traversingList->link;
    }
    return erases;
}
