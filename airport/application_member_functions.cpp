#include <iostream>
#include <cstring>
#include <ctime>
#include "flight.h"     //includes "application.h"

application::application(int Id, string Name, string Surname, string Dest, time_t Airpot_arr, time_t Dest_arr, char Class)
{
    id = Id;
    name = Name;
    surname = Surname;
    destination = Dest;
    arrive_at_airport = Airpot_arr;
    arrive_at_destination = Dest_arr;
    A_or_B_class = Class;
}


string application::get_name() const
{
    string full_name;
    full_name = name;
    full_name += " ";
    full_name += surname;
    return full_name;
}

int application::matches(const flight& my_flight) const
{
    //check for available seats in "add_passenger" (class flight)

    int departure_check = (arrive_at_airport <= my_flight.departs_at())? 1 : 0;             //arrive before a flight takes off
    int arrival_check = (my_flight.arrives_at() <= arrive_at_destination)? 1 : 0;           //flight arrives within limits
    int destination_check = (destination.compare(my_flight.get_destination()) == 0)? 1: 0;  //correct destination

    return ((departure_check == 1)&&(arrival_check == 1)&&(destination_check == 1))? 1: 0;
}
