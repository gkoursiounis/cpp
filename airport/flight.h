#include <list>
#include "application.h"

typedef list <application> application_list;

class flight{
private:
    string destination;                     //case sensitive
    int departure_time;
    int duration;
    int max_passengers_class_A;
    int current_passengers_class_A;
    int max_passengers_class_B;
    int current_passengers_class_B;
    application_list applications;          //empty list
public:
    flight(string , int, int, int, int);

    int add_passenger(const application&);  //1 if passenger is added, else 0
    int cancel_reservations(int);           //returns the number of ERASED passengers

    int departs_at() const { return departure_time; }
    int arrives_at() const { return departure_time + duration; }
    application_list get_bookings() const { return applications; }

    string get_destination() const { return destination; }

    void get_available(int& i, int& j, int& k) const
    {
        i = max_passengers_class_A + max_passengers_class_B - current_passengers_class_A - current_passengers_class_B;
        j = max_passengers_class_A - current_passengers_class_A;
        k = max_passengers_class_B - current_passengers_class_B;
    }
};
