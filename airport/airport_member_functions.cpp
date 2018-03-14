#include <iostream>
#include <cstring>
#include <ctime>
#include "flight.h"
#include "airport.h"


airport::airport(time_t c_time, int c_terminals)
{
    current_time = c_time;
    terminals = c_terminals;
    we_canceled_applications = 0;

    terminal_list = new flight*[terminals];     //array of pointers to flights...these are our terminals
    for(int i=0; i<terminals; i++)
        terminal_list[i] = NULL;

    cout << "Airport created " << endl;
}



airport::~airport()
{
    cout << "Airport deleted" << endl;

    for(int i=0 ; i<terminals; i++)
        if(terminal_list[i] != NULL)
            delete terminal_list[i];
    delete terminal_list;
}



void airport::add_application(int Id, string Name, string Surname, string Dest, time_t Airpot_arr, time_t Dest_arr, char Class)
{
    application new_app(Id, Name, Surname, Dest, Airpot_arr, Dest_arr, Class);
    waiting_list.push_back(new_app);
}



void airport::cancel_applications(int id)
{
    list<application>::iterator t = waiting_list.begin();   //1. erase from "waiting list"
    const unsigned int size_l = waiting_list.size();

    for(unsigned int i=0; i<size_l; i++)
    {
        if(t->get_id() == id)                               //if id found erase...
        {
            cout << "Passenger with id " << id
                 << " and name " << t->get_name()
                 << " was erased from waiting list"
                 << endl;

            t = waiting_list.erase(t);
            we_canceled_applications++;
        }
        else
            t++;                                            //else, move
    }

    for(int i=0; i<terminals; i++)                          //2. erase from reservations
    {
        if(terminal_list[i] == NULL)
            continue;

        we_canceled_applications += terminal_list[i]->cancel_reservations(id);
    }
}



int airport::add_flight(string flight_destination, int dept_time, int flight_duration, int max_class_A, int max_class_B)
{
    for(int i=0; i<terminals; i++)
        if(terminal_list[i] == NULL)        //flight is added at the first available terminal (not NULL)..
        {
            flight *new_flight = new flight(flight_destination, dept_time, flight_duration, max_class_A, max_class_B);
            terminal_list[i] = new_flight;
            return i;
        }
    return -1;                              //..else, no available terminals
}



void airport::cancel_flight(int terminal)
{
    if(terminal<0 || terminal>=terminals || terminal_list[terminal] == NULL) //invalid parameter
        return;

    cout << "Canceling flight to "
         << terminal_list[terminal]->get_destination()
         << " at terminal " << terminal << endl;

    application_list temp_list = terminal_list[terminal]->get_bookings();   //get passenger list

    list<application>::iterator t = temp_list.begin();                      //add passengers to "waiting_list"
    for(unsigned int i=0; i<temp_list.size(); i++)
    {
        waiting_list.push_front(*t);
        we_canceled_applications++;                                         //one more canceled application
        t++;
    }
    delete terminal_list[terminal];                                         //delete flight
    terminal_list[terminal] = NULL;
}



void airport::show_people_waiting()
{
    cout << "Total people waiting: " << waiting_list.size() << endl;

    list<application>::iterator t = waiting_list.begin();
    for(unsigned int i=0; i<waiting_list.size(); i++)
    {
        cout << t->get_name() << endl;
        t++;
    }
}



void airport::flow_time(time_t amount_of_time_that_flows)
{
    for(time_t i=0; i<=amount_of_time_that_flows; i++)
    {
        for(int j=0; j<terminals; j++)
        {
            if(terminal_list[j] == NULL)
                continue;

            if(terminal_list[j]->departs_at() == current_time)              //flight takes off
            {
                cout << "Flight at terminal " << j << " with destination "
                << terminal_list[j]->get_destination() << " just took off"
                << endl << "Passenger List:" << endl;

                application_list passengers = terminal_list[j]->get_bookings();

                list<application>::iterator t = passengers.begin();
                for(unsigned int k=0; k<passengers.size(); k++)
                {
                    cout << t->get_name() << endl;
                    t++;
                }
                cout << endl;

                delete terminal_list[j];
                terminal_list[j] = NULL;
            }
        }
        current_time++;
    }

    current_time--;                                              //last loop: time increased but "for" didn't run

    list<application>::iterator t = waiting_list.begin();                   //check out for outdated applications
    const unsigned int size_l = waiting_list.size();

    for(unsigned int i=0; i<size_l; i++)
    {
        if(t->arrived_by() <= current_time)
        {
            cout << "Canceling application with name " << t->get_name()
                 << " and id " << t->get_id()
                 << " because current time exceeded his arrival time" << endl;
            we_canceled_applications++;
            t = waiting_list.erase(t);
        }
        else
            t++;
    }
}



void airport::boarding()
{
    const unsigned int size_l = waiting_list.size();                            //process is about "waiting list"

    for(unsigned int i=0; i<size_l; i++)
    {
        int flight_found = 0;
        application app = waiting_list.front();                                 //take 1st element

        for(int j=0; j<terminals; j++)                                          //for every terminal
            if(terminal_list[j] != NULL && app.matches(*terminal_list[j]) == 1) //check if flight matches
            {
                if(terminal_list[j]->add_passenger(app) == 1)                   //if seats available, add him..
                {

                    cout << "Passenger with id " << app.get_id()
                         << " and name " << app.get_name()
                         << " boarded on flight to "
                         << terminal_list[j]->get_destination()
                         << " at terminal " << j << endl;

                    waiting_list.pop_front();
                    flight_found = 1;
                }
                break;
            }

        if(flight_found == 0)                                                   //Put him to the end of the list if:
        {                                                                       //(case 1)..flight FOUND but NO
            waiting_list.pop_front();                                           //seats available
            waiting_list.push_back(app);                                        //(case 2) flight NOT FOUND
        }
    }
}



void swap_terminals(flight **a, flight **b)     //help 1
{
    flight* temp = *a;
    *a = *b;
    *b =  temp;
}


void swap_terminal_order(int *a, int *b)        //help 2
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


void airport::show_timetable() const
{
    cout << "AVAILABLE flights in terminals" << endl;

    for(int i=0; i<terminals; i++)                                          //print AVAILABLE flights
    {
        if(terminal_list[i] == NULL)                                        //we DON'T print empty terminals...
            continue;

        int a, b, c;
        terminal_list[i]->get_available(a, b, c);

        if(a == 0)                                                          //..or flights with no available seats
            continue;

        cout << "  Terminal: " << i << endl <<
                "   Destination: " << terminal_list[i]->get_destination() <<
                endl << endl;
    }

    flight **temp_list = new flight*[terminals];                            //copy flight pointers to a help array
    for(int i=0; i<terminals; i++)
        temp_list[i] = terminal_list[i];

    int numbers[terminals];                                                 //copy initial terminal numbers
    for(int i=0; i<terminals; i++)                                          //bubble sort will change their order
        numbers[i] = i;


    for(int i=1; i<terminals; i++)                                          //bubble sort (by ~ip/K04.pdf)
    {
        for (int j=terminals-1 ; j >= i ; j--)
            if(temp_list[j-1] == NULL || temp_list[j] == NULL)
            {
                swap_terminals(&temp_list[j-1], &temp_list[j]);
                swap_terminal_order(&numbers[j-1], &numbers[j]);

            }
            else if(temp_list[j-1]->departs_at() > temp_list[j]->departs_at())
            {
                swap_terminals(&temp_list[j-1], &temp_list[j]);
                swap_terminal_order(&numbers[j-1], &numbers[j]);
            }
    }

    cout << endl << "ALL flights in terminals (sorted)" << endl;            //print ALL flights (sorted)

    for(int i=0; i<terminals; i++)
    {
        if(temp_list[i] == NULL)
            continue;

        cout << "  Terminal: " << numbers[i] << endl
             << "   Destination: " << temp_list[i]->get_destination() << endl
             << "   Departs at: " << temp_list[i]->departs_at() << endl
             << "   Arrives at: " << temp_list[i]->arrives_at() << endl;

        int a, b, c;
        temp_list[i]->get_available(a, b, c);
        cout << "   Available seats: " << a << " (class A) " << b
        << " (class B) " << c << endl << endl;
    }
    delete[] temp_list;                                                     //delete help array
}
