#include <iostream>
#include <cstring>
#include "flight.h"     //includes "application.h"


flight::flight(string flight_destination, int dept_time, int flight_duration, int max_class_A, int max_class_B)
{
    destination = flight_destination;
    departure_time = dept_time;
    duration = flight_duration;
    max_passengers_class_A = max_class_A;
    max_passengers_class_B = max_class_B;

    current_passengers_class_A = 0;
    current_passengers_class_B = 0;
}


int flight::add_passenger(const application& my_application)        //availability check & boarding
{
    int class_A, class_B, all;
    get_available(all, class_A, class_B);

    if(my_application.is_luxury_class() == 1 && class_A != 0)       //class A - available seats
    {
        applications.push_back(my_application);
        current_passengers_class_A++;
        return 1;
    }
    else if(my_application.is_luxury_class() == 0 && class_B != 0)  //class B - available seats
    {
        applications.push_back(my_application);
        current_passengers_class_B++;
        return 1;
    }
    else
       return 0;                                                    //NO available seats
}


int flight::cancel_reservations(int id)
{
    int erased = 0;
    list<application>::iterator t = applications.begin();
    const unsigned int size_l = applications.size();

    for(unsigned int i=0; i<size_l; i++)
    {
        if(t->get_id() == id)                                       //if id found then erase...
        {
            cout << "Passenger with id " << id
                 << " erased form reservations" << endl;

            if(t->is_luxury_class() == 1)
                current_passengers_class_A--;
            else
                current_passengers_class_B--;

            t = applications.erase(t);
            erased++;
        }
        else
            t++;                                                    //...else, move
    }
    return erased;
}
