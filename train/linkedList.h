class passenger{
private:
    int hasTicket;
    int hasDiscount;
    int iwasCaught;     //1 if check caught passenger, else 0
    int myNumber;       //every passenger has a unique number in the waggon list
public:
    passenger();

    void setCatch() { iwasCaught = 1; }
    void setNumber(int counter) { myNumber = counter; }

    int getTicket() const { return hasTicket; }
    int getDiscount() const { return hasDiscount; }
    int getChatch() const { return iwasCaught; }
    int getNumber() const { return myNumber; }
};

class linkedList{
private:

    struct node{
        passenger Passenger;
        node *link;
    };

    node *head;

public:
    linkedList();
    ~linkedList();

    void insertPassenger();
    void deletePassenger(int);
    int  findPassenger(int);                    //return the "hasTicket" value of passenger with "myNumber" = n
    int markOffenders();
    int deleteOffenders(int&, const int, int&);

    void print() const;                         //print total passengers
};
