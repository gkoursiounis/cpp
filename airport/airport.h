#include <list>
using namespace std;

class flight;
class application;

typedef list <application> application_list;

class airport{
private:
    int terminals;                                  //TERMINALS from 0 to terminals - 1
    flight **terminal_list;                         //terminals: array of pointers to flights
    int current_time;
    int we_canceled_applications;
    application_list waiting_list;                  //empty list
public:
    airport(time_t, int);
    ~airport();

    void add_application(int , string , string , string , time_t, time_t, char);
    void cancel_applications(int);

    int add_flight(string, int, int, int, int);     //returns the number of terminal
    void cancel_flight(int);

    void show_people_waiting();
    void flow_time(time_t);
    void boarding();                                //put passengers into airplane if flight "matches"

    time_t get_time() const { return current_time; }
    int failed_applications() const { return we_canceled_applications; }
    void show_timetable() const;
};
