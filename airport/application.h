class flight;

using namespace std;

class application{
private:
    int id;
    string name;
    string surname;
    string destination;                 //case sensitive
    time_t arrive_at_airport;
    time_t arrive_at_destination;
    char A_or_B_class;
public:
    application(int , string , string , string , time_t, time_t, char);

    string get_name() const;
    int matches(const flight&) const;   //1 if flight matches, else 0

    int is_luxury_class() const { return (A_or_B_class == 'A' || A_or_B_class == 'a')? 1 : 0; }
    int get_id() const { return id; }
    int arrived_by()const { return arrive_at_destination; }
};
