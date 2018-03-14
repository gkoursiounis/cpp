#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include "airport.h"

int main(int argc, char *argv[])
{
    time_t time;                                    //recommended time = 2

    if(argc==2)
        time = atoi(argv[1]);
    else
    {
        cout << "Usage: " << argv[0] << " <time>" << endl;
        return 1;
    }


    airport athens(4, 3);                           //current time & terminals


    ifstream flights("flights");                    //read flights
    if(!flights)
    {
        cout << "Cannot open file" << endl;
        return 1;
    }

    string destination;
    int number_of_flights, departure_time, duration, max_passengers_class_A, max_passengers_class_B;

    flights >> number_of_flights;

    for(int i=0; i<number_of_flights; i++)
    {
        flights >> destination;
        flights >> departure_time >> duration >>
                max_passengers_class_A >> max_passengers_class_B;

        cout << "A flight added at terminal: " <<
             athens.add_flight(destination, departure_time, duration, max_passengers_class_A, max_passengers_class_B)
             << endl;
    }
    flights.close();


    ifstream applications("applications");      //read applications
    if(!applications)
    {
        cout << "Cannot open file" << endl;
        return 1;
    }

    string name, surname, p_destination;
    int number_of_apps, id, airport_arr, dest_arr;
    char p_class;

    applications >> number_of_apps;

    for(int i=0; i<number_of_apps; i++)
    {
        applications >> id;
        applications >> name >> surname >> p_destination;
        applications >> airport_arr >> dest_arr >> p_class;

        athens.add_application(id, name, surname, p_destination, airport_arr, dest_arr, p_class);
    }
    applications.close();


    cout << endl << " - Boarding - " << endl;   //put passengers on planes
    athens.boarding();
    cout << endl << " - Timetable - " << endl;  //print timetable
    athens.show_timetable();
    cout << endl;

    //extras

    athens.show_people_waiting();
    cout << endl;
    athens.cancel_flight(2);                    //flight to THESSALONIKI is canceled
    cout << endl;                               //passenger Bjarne Stroustrup in "waiting list" (id 5)
    athens.show_people_waiting();
    cout << endl;

    athens.cancel_applications(5);              //delete passenger Bjarne Stroustrup :(
    cout << endl;

    //

    cout << "Current time: " << athens.get_time() << endl;
    athens.flow_time(time);
    cout << "Current time: " << athens.get_time() << endl;

    cout << endl << " - Timetable - " << endl;  //print timetable
    athens.show_timetable();                    //if ALL terminals are EMPTY then we print
    cout << endl;                               //only the titles

    return 0;
}

